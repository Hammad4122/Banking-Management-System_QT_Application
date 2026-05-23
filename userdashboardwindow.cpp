#include "userdashboardwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QLocale>
#include <QHeaderView>
#include <QDebug>

UserDashboardWindow::UserDashboardWindow(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("userDashContent");

    // ── Root layout ────────────────────────────────────────────────
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 0);
    mainLayout->setSpacing(10);

    // ════════════════════════════════════════════════════════════════
    //  TOP ROW: Debit card  |  Income card  |  Expense card
    // ════════════════════════════════════════════════════════════════
    QHBoxLayout *cardRow = new QHBoxLayout();
    cardRow->setSpacing(15);

    // ── Debit Card ─────────────────────────────────────────────────
    QWidget *debitCard = new QWidget();
    debitCard->setObjectName("dashDebitCard");
    debitCard->setFixedSize(350, 220);

    QVBoxLayout *cardVLayout = new QVBoxLayout(debitCard);
    cardVLayout->setContentsMargins(0, 0, 0, 60); // leave room for highlight

    // Chip icon
    creditChipLabel = new QLabel();
    QPixmap chipPix(":/resources/chip.png");
    creditChipLabel->setPixmap(chipPix.scaled(45, 45,
                                              Qt::KeepAspectRatio, Qt::SmoothTransformation));
    creditChipLabel->setContentsMargins(10, 10, 0, 0);

    // Card header (chip + expiry)
    QHBoxLayout *cardHeaderLayout = new QHBoxLayout();
    cardExpiryLabel = new QLabel();
    cardExpiryLabel->setContentsMargins(0, 0, 10, 0);
    cardHeaderLayout->addWidget(creditChipLabel, 0, Qt::AlignLeft);
    cardHeaderLayout->addStretch();
    cardHeaderLayout->addWidget(cardExpiryLabel, 0, Qt::AlignRight);

    // Balance label
    userBalance = new QLabel();
    userBalance->setContentsMargins(10, 0, 0, 0);

    // Card holder label
    cardHolderLabel = new QLabel();
    cardHolderLabel->setContentsMargins(10, 0, 0, 0);

    cardVLayout->addLayout(cardHeaderLayout);
    cardVLayout->addWidget(userBalance);
    cardVLayout->addWidget(cardHolderLabel);
    cardVLayout->addStretch();

    // ── Card Highlight Section (bottom strip) ──────────────────────
    QWidget *cardHighlight = new QWidget(debitCard);
    cardHighlight->setObjectName("cardHighlightSection");
    cardHighlight->setGeometry(0, 160, 350, 60);

    QHBoxLayout *highlightLayout = new QHBoxLayout(cardHighlight);

    cardNumber = new QLabel();
    cardNumber->setContentsMargins(10, 0, 0, 0);

    creditCircles = new QLabel();
    QPixmap circlesPix(":/resources/master_card_overlapping-circles.png");
    creditCircles->setPixmap(circlesPix.scaled(50, 50,
                                               Qt::KeepAspectRatio, Qt::SmoothTransformation));
    creditCircles->setContentsMargins(0, 0, 5, 0);

    highlightLayout->addWidget(cardNumber,     0, Qt::AlignLeft);
    highlightLayout->addWidget(creditCircles,  0, Qt::AlignRight | Qt::AlignVCenter);

    // ── Income Card ────────────────────────────────────────────────
    QWidget *incomeCard = new QWidget();
    incomeCard->setObjectName("incomeCard");
    incomeCard->setFixedSize(390, 220);

    QVBoxLayout *incomeLayout = new QVBoxLayout(incomeCard);

    incomeTitleLabel = new QLabel("Income");
    incomeTitleLabel->setStyleSheet(
        "color: #718096; font-weight: 600; font-size: 14px;");

    incomeAmountLabel = new QLabel("$0.00");
    incomeAmountLabel->setObjectName("incomeAmountLabel");

    incomeLayout->addWidget(incomeTitleLabel);
    incomeLayout->addWidget(incomeAmountLabel);
    incomeLayout->addStretch();

    // ── Expense Card ───────────────────────────────────────────────
    QWidget *expenseCard = new QWidget();
    expenseCard->setObjectName("expenseCard");
    expenseCard->setFixedSize(390, 220);

    QVBoxLayout *expenseLayout = new QVBoxLayout(expenseCard);

    expenseTitleLabel = new QLabel("Expense");
    expenseTitleLabel->setStyleSheet(
        "color: #718096; font-weight: 600; font-size: 14px;");

    expenseAmountLabel = new QLabel("$0.00");
    expenseAmountLabel->setObjectName("expenseAmountLabel");

    expenseLayout->addWidget(expenseTitleLabel);
    expenseLayout->addWidget(expenseAmountLabel);
    expenseLayout->addStretch();

    // Assemble top row
    cardRow->addWidget(debitCard, 0, Qt::AlignLeft);
    cardRow->addWidget(incomeCard);
    cardRow->addWidget(expenseCard);

    // ════════════════════════════════════════════════════════════════
    //  MIDDLE ROW: Quick action buttons
    // ════════════════════════════════════════════════════════════════
    QWidget *actionWidget = new QWidget();
    actionWidget->setFixedWidth(380);

    QHBoxLayout *actionLayout = new QHBoxLayout(actionWidget);
    actionLayout->setContentsMargins(0, 2, 0, 2);
    actionLayout->setSpacing(8);

    depositBtn  = new QPushButton("Deposit");
    transferBtn = new QPushButton("Transfer");
    withdrawBtn = new QPushButton("Withdraw");

    depositBtn->setObjectName("depositBtn");
    transferBtn->setObjectName("transferBtn");
    withdrawBtn->setObjectName("withdrawBtn");

    depositBtn->setCursor(Qt::PointingHandCursor);
    transferBtn->setCursor(Qt::PointingHandCursor);
    withdrawBtn->setCursor(Qt::PointingHandCursor);

    actionLayout->addWidget(depositBtn);
    actionLayout->addWidget(transferBtn);
    actionLayout->addWidget(withdrawBtn);

    // ════════════════════════════════════════════════════════════════
    //  BOTTOM ROW: Transaction history table
    // ════════════════════════════════════════════════════════════════
    transactionTable = new QTableView(this);
    transactionTable->setObjectName("transactionTable");
    transactionTable->setFixedHeight(210);
    transactionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    transactionTable->setSelectionMode(QAbstractItemView::SingleSelection);
    transactionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transactionTable->setShowGrid(false);
    transactionTable->verticalHeader()->setVisible(true);
    transactionTable->setFocusPolicy(Qt::NoFocus);
    transactionTable->setAlternatingRowColors(true);
    transactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // ── Assemble page ──────────────────────────────────────────────
    mainLayout->addLayout(cardRow);
    mainLayout->addWidget(actionWidget);
    mainLayout->addWidget(transactionTable);
    mainLayout->addStretch();

    // ── Button connections ─────────────────────────────────────────
    connect(depositBtn,  &QPushButton::clicked,
            this, &UserDashboardWindow::onDepositClicked);
    connect(transferBtn, &QPushButton::clicked,
            this, &UserDashboardWindow::onTransferClicked);
    connect(withdrawBtn, &QPushButton::clicked,
            this, &UserDashboardWindow::onWithdrawClicked);
}

// ─── Session loading ──────────────────────────────────────────────────────────

void UserDashboardWindow::loadSession(UserSessionHandler *session)
{
    m_session = session;

    // ── Income / Expense ───────────────────────────────────────────
    incomeAmountLabel->setText(
        "$" + QString::number(session->getIncome(), 'f', 2));
    expenseAmountLabel->setText(
        "$" + QString::number(session->getExpense(), 'f', 2));

    // ── Balance (formatted with commas) ───────────────────────────
    QLocale locale(QLocale::English);
    QString fmt = locale.toString(session->getBalance(), 'f', 2);
    userBalance->setText(
        QString("<span style='font-size:13px;font-weight:600;"
                "color:rgba(255,255,255,0.5);'>Balance</span><br>"
                "<span style='font-size:20px;font-weight:bold;"
                "color:white;'>$%1</span>").arg(fmt));

    // ── Card holder ────────────────────────────────────────────────
    cardHolderLabel->setText(
        QString("<span style='font-size:10px;color:rgba(255,255,255,0.5);'>"
                "CARD HOLDER</span><br>"
                "<span style='font-size:14px;font-weight:bold;color:white;'>"
                "%1</span>").arg(session->getFullName().toUpper()));

    // ── Expiry ─────────────────────────────────────────────────────
    cardExpiryLabel->setText(
        QString("<span style='font-size:10px;color:rgba(255,255,255,0.5);'>"
                "VALID THRU</span><br>"
                "<span style='font-size:14px;font-weight:bold;color:white;'>"
                "04/31</span>"));

    // ── Card number ────────────────────────────────────────────────
    cardNumber->setText("5123  ****  ****  8892");
    cardNumber->setStyleSheet(
        "font-weight:600; font-size:20px; font-family:'Roboto';");

    // ── Transaction table ──────────────────────────────────────────
    transactionTable->setModel(db.getTransactionHistory(session->getAccountID()));
}

// ─── Private helpers ──────────────────────────────────────────────────────────

void UserDashboardWindow::refreshBalanceAndTable()
{
    if (!m_session) return;

    double fresh = db.getBalance(m_session->getAccountID());
    m_session->setBalance(fresh);

    QLocale locale(QLocale::English);
    QString fmt = locale.toString(fresh, 'f', 2);
    userBalance->setText(
        QString("<span style='font-size:13px;font-weight:600;"
                "color:rgba(255,255,255,0.5);'>Balance</span><br>"
                "<span style='font-size:20px;font-weight:bold;"
                "color:white;'>$%1</span>").arg(fmt));

    incomeAmountLabel->setText(
        "$" + QString::number(db.getIncome(m_session->getAccountID()), 'f', 2));
    expenseAmountLabel->setText(
        "$" + QString::number(db.getExpenses(m_session->getAccountID()), 'f', 2));

    transactionTable->setModel(db.getTransactionHistory(m_session->getAccountID()));
}

void UserDashboardWindow::openTransactionDialog(TransactionType type)
{
    if (!m_session) return;

    TransactionDialog *dlg = new TransactionDialog(type, m_session, this);
    dlg->setModal(true);
    dlg->setAttribute(Qt::WA_DeleteOnClose);

    connect(dlg, &TransactionDialog::updateBalance,
            this, &UserDashboardWindow::refreshBalanceAndTable);

    dlg->show();
}

// ─── Slots ────────────────────────────────────────────────────────────────────

void UserDashboardWindow::onDepositClicked()  { openTransactionDialog(DEPOSIT);  }
void UserDashboardWindow::onTransferClicked() { openTransactionDialog(TRANSFER); }
void UserDashboardWindow::onWithdrawClicked() { openTransactionDialog(WITHDRAW); }
