# 🏦 Banking Management System

A desktop banking application built with **C++**, **Qt6**, and **Microsoft SQL Server**, featuring a modern UI, secure user authentication, real-time transaction management, and a dual-theme design system.

---

## 📸 Screenshots

| Login Page |
|---|
<img width="1797" height="1016" alt="Screenshot 2026-05-24 194822" src="https://github.com/user-attachments/assets/a24c7812-39aa-45fa-80e9-d811f73d7e87" />
<img width="1796" height="1011" alt="Screenshot 2026-05-24 195101" src="https://github.com/user-attachments/assets/ee6d9e47-4c76-4f65-a166-725e2549cc58" />


| Signup Page |
|---|
<img width="899" height="471" alt="Screenshot 2026-05-15 232304" src="https://github.com/user-attachments/assets/3669fbaa-9f09-4a56-8a06-01ea9ab177fc" />
<img width="897" height="473" alt="image" src="https://github.com/user-attachments/assets/b6568e56-fd1f-473b-a2c7-2d5b1bef7704" />


| Dashboard |
|---|
<img width="898" height="473" alt="Screenshot 2026-05-15 231040" src="https://github.com/user-attachments/assets/f3b189c9-9e74-4001-9aac-ee31a48f5af9" />
<img width="897" height="472" alt="Screenshot 2026-05-15 231112" src="https://github.com/user-attachments/assets/2a7ae0e6-2de5-499e-8c42-3d4208c371cd" />
<img width="1796" height="1014" alt="Screenshot 2026-05-24 194847" src="https://github.com/user-attachments/assets/a9653751-32e6-483d-9a5a-b00da986ab09" />
<img width="1798" height="1014" alt="Screenshot 2026-05-24 194909" src="https://github.com/user-attachments/assets/99b85bc7-03dd-41bf-816f-4c9de54c5293" />
<img width="1798" height="1019" alt="Screenshot 2026-05-24 194927" src="https://github.com/user-attachments/assets/5d7ff9e4-d55a-44c3-a8dc-63d68da28f98" />
<img width="1798" height="1018" alt="Screenshot 2026-05-24 194943" src="https://github.com/user-attachments/assets/ba100384-2dc6-4035-859c-d610f87f8362" />






| Transaction Dialog |
|---|

  | Deposit Dialog |
 
  <img width="296" height="222" alt="Screenshot 2026-05-15 232421" src="https://github.com/user-attachments/assets/5d2640cf-ba5d-4dc6-b5c6-a8422e767a47" />
  <img width="298" height="224" alt="image" src="https://github.com/user-attachments/assets/b7d1539f-b906-44ec-8331-34064a34621f" />



  | Transfer Dialog |
  
  <img width="298" height="292" alt="Screenshot 2026-05-15 232449" src="https://github.com/user-attachments/assets/d903c514-8499-462c-8ebb-b0a46c437527" />
  <img width="299" height="293" alt="image" src="https://github.com/user-attachments/assets/357af126-f1cd-486b-8efb-ab295df1fadd" />


  
  | Withdraw Dialog |
  
  <img width="296" height="222" alt="Screenshot 2026-05-15 232505" src="https://github.com/user-attachments/assets/f799c23f-08ad-4845-939a-9fcf1125bfb0" />
  <img width="298" height="222" alt="image" src="https://github.com/user-attachments/assets/7b66e8d4-c7aa-4103-947a-534cfaeef91d" />


| TPIN Verification |
|---|
<img width="221" height="155" alt="Screenshot 2026-05-15 232544" src="https://github.com/user-attachments/assets/be1df9bd-9290-4756-aa88-b9ac9b7f95bf" />
<img width="224" height="155" alt="image" src="https://github.com/user-attachments/assets/3c1076e5-53a6-4344-afc0-dc4a92985020" />


---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [System Architecture](#system-architecture)
- [Database Schema](#database-schema)
- [Project Structure](#project-structure)
- [Security Model](#security-model)
- [UI & Theme System](#ui--theme-system)
- [Admin Dashboard](#admin-dashboard)
- [Getting Started](#getting-started)
- [How to Clone and Run](#how-to-clone-and-run)
- [Known Limitations & Future Work](#known-limitations--future-work)

---

## Overview

The Banking Management System (BMS) is a full-stack desktop application simulating core banking operations. It supports user registration and login, account management, and financial transactions (deposits, withdrawals, and transfers) — all persisted to a Microsoft SQL Server database via ODBC.

The project was developed as part of a 2nd-semester Software Engineering course and demonstrates applied use of OOP principles, relational database design, Qt's signal-slot mechanism, and layered software architecture.

---

## Features

- **User Authentication** — Signup, login, and session management with SHA-256 hashed passwords.
- **TPIN (Transaction PIN)** — A separate 4-digit security PIN, also SHA-256 hashed, required to authorize any financial operation.
- **Deposit / Withdraw / Transfer** — Full transaction lifecycle with input validation, balance checks, and persistent logging.
- **Transaction History** — A read-only table view showing all past transactions for the logged-in user, sorted newest-first.
- **Income & Expense Summary** — Aggregated totals shown on the dashboard via SQL `SUM()` queries.
- **Real-Time Balance Update** — After any transaction, balance and summary cards refresh live without a page reload.
- **Dual Theme System** — A globally toggled Light Blue theme and Dark Emerald theme, persistent across all pages within a session.
- **Success Animation** — A GIF animation plays on successful transactions before the dialog auto-closes.
  <img width="298" height="225" alt="Screenshot 2026-05-15 232607" src="https://github.com/user-attachments/assets/fd41a582-7192-4d15-a5bb-e5a48237d949" />

- **Cross-Platform DB Support** — Windows uses local Windows Authentication; Linux uses remote SQL Auth via ODBC.
- **Admin Dashboard** — A dedicated admin panel accessible via a role selector on the login screen, providing a system-wide overview and management tools without exposing user-facing transaction features.
  - **Overview Tab** — Stat cards showing total registered users, total system balance, total deposits, and total withdrawals across all accounts, with a manual refresh button.
  - **Users Tab** — A searchable, read-only table listing all registered users, filterable in real time by name, username, or email.
  - **Accounts Tab** — A read-only table of all accounts with balances, refreshable on demand.
  - **Credentials Tab** — A secure form allowing the admin to update their own username and/or password; requires the current password for verification before any change is committed.

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| UI Framework | Qt 6 (Widgets, Sql modules) |
| Build System | CMake 3.16+ |
| Database | Microsoft SQL Server (via SSMS) |
| DB Driver | Qt ODBC (`QODBC`) |
| IDE | Qt Creator |
| Password Hashing | Qt `QCryptographicHash` (SHA-256) |
| Styling | Qt Style Sheets (QSS) |

---

## System Architecture

The application follows a **layered architecture** with clear separation between the UI, session, and data access layers.

```
┌──────────────────────────────────────────┐
│              Presentation Layer           │
│  LoginWindow │ SignupWindow │ Dashboard   │
│  UserDashboardWindow │ AdminDashboard     │
│  TransactionDialog │ TPinDialog           │
│         (Qt Widgets + QSS Themes)         │
└────────────────────┬─────────────────────┘
                     │  Qt Signals & Slots
┌────────────────────▼─────────────────────┐
│            Orchestration Layer            │
│               MainWindow                  │
│         (QStackedWidget Router)           │
└────────────────────┬─────────────────────┘
                     │
┌────────────────────▼─────────────────────┐
│             Session Layer                 │
│           UserSessionHandler              │
│  (In-memory user state: ID, name,         │
│   balance, income, expense, accountID)    │
└────────────────────┬─────────────────────┘
                     │
┌────────────────────▼─────────────────────┐
│           Data Access Layer (DAL)         │
│                  BankDB                   │
│   (All SQL queries, schema init, ODBC)    │
└────────────────────┬─────────────────────┘
                     │  QODBC
┌────────────────────▼─────────────────────┐
│         Microsoft SQL Server (BankDB)     │
│     Users │ Accounts │ Transactions       │
└──────────────────────────────────────────┘
```

### Key Design Decisions

**`BasePage` as the shared base class** — All page widgets (`LoginWindow`, `SignupWindow`, `DashboardWindow`) inherit from `BasePage` rather than directly from `QWidget`. `BasePage` owns the shared `BankDB` instance, the static `isDarkMode` flag, and theme application logic. This avoids duplicating database connections and theme code across every page.

**`MainWindow` as the router** — `MainWindow` owns a `QStackedWidget` and manages all page transitions by reacting to signals emitted from child pages (e.g., `loginSuccessful`, `signupRequested`, `logoutRequested`). No page directly navigates to another; all routing is centralized.

**`UserSessionHandler` as the session object** — After login, a `UserSessionHandler` is heap-allocated by `BankDB::setUserInfo()` and passed up to `MainWindow`, which then injects it into the `DashboardWindow`. This decouples the database from the dashboard UI.

**Signal-Slot for theme changes** — Each page emits a `themeChangeRequested` signal; `MainWindow` catches it, calls `BasePage::toggleGlobalTheme()` (which flips the static bool), then calls `applyCurrentTheme()` on all three pages. This keeps theme state globally consistent without any page needing to know about the others.

**`DashboardWindow` as a sub-dashboard router** — Rather than a single monolithic dashboard, `DashboardWindow` wraps a `QStackedWidget` containing `UserDashboardWindow` and `AdminDashboardWindow` as two independent sub-widgets. `MainWindow` calls either `initializeUserDashboard()` or `initializeAdminDashboard()` after login, which switches the stack index and loads the appropriate data. This keeps user and admin concerns cleanly separated while sharing the common header.

---

## Database Schema

The schema is auto-initialized on first connection via `BankDB::initializeSchema()`, using `IF NOT EXISTS` guards so re-runs are safe.

```sql
-- Users Table
CREATE TABLE Users (
    user_id    INT PRIMARY KEY IDENTITY(1,1),
    first_name NVARCHAR(30)  NOT NULL,
    last_name  NVARCHAR(30)  NOT NULL,
    user_name  NVARCHAR(15)  UNIQUE NOT NULL,
    email      NVARCHAR(100) UNIQUE NOT NULL,
    password   NVARCHAR(64)  NOT NULL,   -- SHA-256 hex hash
    tpin       NVARCHAR(64)  NOT NULL,   -- SHA-256 hex hash (added via ALTER)
    mobile_no  NVARCHAR(11)  UNIQUE NOT NULL,
    created_at DATETIME      DEFAULT GETDATE()
);

-- Accounts Table
CREATE TABLE Accounts (
    account_id INT PRIMARY KEY IDENTITY(1000,1),  -- Starts at 1000 for realism
    user_id    INT            NOT NULL,
    balance    DECIMAL(18,2)  DEFAULT 0.00,
    currency   NVARCHAR(10)   DEFAULT 'PKR',
    CONSTRAINT FK_UserAccount FOREIGN KEY (user_id)
        REFERENCES Users(user_id) ON DELETE CASCADE
);

-- Transactions Table
CREATE TABLE Transactions (
    transaction_id   INT PRIMARY KEY IDENTITY(1,1),
    account_id       INT            NOT NULL,
    transaction_type NVARCHAR(20)   NOT NULL,   -- 'Deposit', 'Withdrawal'
    amount           DECIMAL(18,2)  NOT NULL,
    balance_after    DECIMAL(18,2)  NOT NULL,
    remarks          NVARCHAR(255),
    transaction_date DATETIME       DEFAULT GETDATE(),
    CONSTRAINT FK_AccountTransaction FOREIGN KEY (account_id)
        REFERENCES Accounts(account_id) ON DELETE CASCADE
);
```

**Relationships:**
- One `User` → One `Account` (1:1, enforced by FK with CASCADE DELETE)
- One `Account` → Many `Transactions` (1:N, enforced by FK with CASCADE DELETE)

---

## Project Structure

```
BankingManagementSystem_Project/
│
├── CMakeLists.txt              # Build configuration (Qt6 Widgets + Sql)
├── main.cpp                    # Application entry point
│
├── basepage.h / .cpp           # Abstract base: DB connection, theme system
├── mainwindow.h / .cpp         # Root window: QStackedWidget router, signal hub
│
├── loginwindow.h / .cpp        # Login UI + credential validation + role selector
├── signupwindow.h / .cpp       # Registration UI + field validation
├── dashboardwindow.h / .cpp    # Shared dashboard shell: header + sub-dashboard router
├── userdashboardwindow.h / .cpp   # User sub-dashboard: debit card, transactions, actions
├── admindashboardwindow.h / .cpp  # Admin sub-dashboard: overview, users, accounts, credentials tabs
│
├── database.h / .cpp           # BankDB class: all SQL operations (DAL)
├── usersessionhandler.h / .cpp # In-memory session state after login
│
├── transactiondialog.h / .cpp  # Modal dialog: Deposit / Withdraw / Transfer
├── tpindialog.h / .cpp         # Modal dialog: 4-digit TPIN verification
├── settingwindow.h / .cpp      # Settings page (stub, not yet implemented)
│
└── resources.qrc               # Qt resource file (icons, images, GIFs)
```

---

## Security Model

| Concern | Implementation |
|---|---|
| Password storage | SHA-256 hashed via `QCryptographicHash` before INSERT |
| TPIN storage | SHA-256 hashed separately from the password |
| Transaction auth | Every financial action requires TPIN verification |
| SQL injection | All queries use `QSqlQuery::prepare()` + `addBindValue()` (parameterized) |
| Input validation | Qt validators (`QDoubleValidator`, `QRegularExpressionValidator`) on all fields |
| Self-transfer | Blocked at application level before query execution |
| Insufficient funds | Balance checked before withdraw/transfer executes |

> **Note:** The database credentials in `database.cpp` are hardcoded for development. In a production system, these should be moved to environment variables or a secure config file, and the connection should use TLS/SSL.

---

## UI & Theme System

The application ships with two complete themes defined as QSS (Qt Style Sheets) string constants in `BasePage`:

**Light Blue Theme** (`lightBlueTheme`)
- Background: `#F5F7FA` (soft off-white)
- Accent: `#2D60FF` (royal blue)
- Cards: white with drop shadows
- Debit card: blue-purple gradient

**Dark Emerald Theme** (`darkEmeraldTheme`)
- Background: `#0B0E11` (near-black)
- Accent: `#50C878` (emerald green)
- Cards: `#161A1E` (dark slate)
- Debit card: green gradient

Theme state is stored as a `static bool BasePage::isDarkMode`. Toggling it and calling `applyCurrentTheme()` on all pages re-styles the entire application instantly. Icons (bank logo, credit card logo) are also swapped to match the active theme via `updateIcons()`.

---

## Admin Dashboard

The admin panel is accessed by selecting **"Login as Admin"** from the role dropdown on the login page. No signup flow exists for admins — credentials are seeded directly in the database.

After a successful admin login, `MainWindow` calls `initializeAdminDashboard()` on `DashboardWindow`, which switches the inner `QStackedWidget` to `AdminDashboardWindow` and calls `loadData()` to populate all views. The shared header (logo, title, theme toggle, logout) remains visible; the account number label is replaced with "Admin Panel".

`AdminDashboardWindow` is organized as a `QTabWidget` with four tabs:

| Tab | Contents |
|---|---|
| 📊 Overview | Four stat cards: total users, total system balance, total deposits, total withdrawals. Manual refresh button. |
| 👥 Users | Searchable table of all registered users (name, username, email, etc.). Filter updates live as you type. |
| 🏦 Accounts | Table of all accounts with balances. Refreshed lazily on tab switch or via the refresh button. |
| 🔐 Credentials | Form to update the admin's own username and/or password. Requires current password verification before any change is saved. |

Stat cards use a colored left-border accent style (`#adminStatCard`) rather than the global theme QSS, so they render consistently regardless of whether the user is in light or dark mode.

---

## Getting Started

### Prerequisites

Make sure the following are installed on your system:

- **Qt 6** (with `QtWidgets` and `QtSql` modules) — [Download Qt](https://www.qt.io/download)
- **Qt Creator** (recommended IDE) — bundled with Qt installer
- **CMake 3.16+**
- **Microsoft SQL Server** (Express edition is sufficient) with **SSMS** for management
- **ODBC Driver for SQL Server**
  - Windows: Usually pre-installed (`SQL Server` driver)
  - Linux: Install `msodbcsql18` — [Microsoft ODBC Docs](https://learn.microsoft.com/en-us/sql/connect/odbc/linux-mac/installing-the-microsoft-odbc-driver-for-sql-server)

### Database Setup

1. Open **SSMS** and connect to your SQL Server instance.
2. Create a new database named `BankDB`:
   ```sql
   CREATE DATABASE BankDB;
   ```
3. The application will auto-create the `Users`, `Accounts`, and `Transactions` tables on first launch via `initializeSchema()`.

### Configure the Connection String

Open `database.cpp` and update the connection strings to match your environment:

**Windows:**
```cpp
connStr = "Driver={SQL Server};"
          "Server=YOUR_PC_NAME\\SQLEXPRESS;"   // e.g. DESKTOP-ABC\\SQLEXPRESS
          "Database=BankDB;"
          "Trusted_Connection=yes;";
```

**Linux:**
```cpp
connStr = "Driver={ODBC Driver 18 for SQL Server};"
          "Server=YOUR_SERVER_IP,1433;"
          "Database=BankDB;"
          "UID=sa;"
          "PWD=YOUR_PASSWORD;"
          "Encrypt=yes;"
          "TrustServerCertificate=yes;";
```

---

## How to Clone and Run

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/BankingManagementSystem.git
cd BankingManagementSystem
```

### 2. Open in Qt Creator

- Launch **Qt Creator**
- Go to **File → Open File or Project**
- Select `CMakeLists.txt` from the cloned folder
- Qt Creator will automatically configure the CMake project

### 3. Configure the Kit

- When prompted, select a **Qt 6 kit** (e.g., `Qt 6.x.x (MinGW)` on Windows or `Qt 6.x.x (GCC)` on Linux)
- Make sure the kit has the `QtSql` module available

### 4. Update DB Credentials

Edit `database.cpp` as described in the [Configure the Connection String](#configure-the-connection-string) section above.

### 5. Build & Run

- Press **Ctrl+R** (or click the green ▶ Run button) in Qt Creator
- The application will build and launch
- On first run, the database tables are created automatically

### Building via Command Line (Optional)

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64
make -j$(nproc)
./BankingManagementSystem_Project
```

---

## Known Limitations & Future Work

- **Hardcoded card number** — The card number on the dashboard (`5123 **** **** 8892`) and expiry date (`04/31`) are static placeholders, not generated per user.
- **`settingwindow.cpp` is a stub** — The settings page class exists but has no implemented functionality yet.
- **No database transactions** — The `transfer()` function performs two sequential SQL operations without wrapping them in a SQL `BEGIN TRANSACTION / COMMIT / ROLLBACK` block. A network failure mid-transfer could leave balances inconsistent.
- **Single account per user** — The schema supports only one account per user. Multi-account support would require schema changes.
- **No password recovery** — There is currently no "Forgot Password" flow.
- **Notification button** — The notification icon in the header is present in the UI but not yet connected to any functionality.

---

## Author

Developed by **Muhammad Hammad Ateeq & Muhammad Shayan Chaudhary**
BSc Software Engineering — 2nd Semester
`Bahria University, Islamabad`

---

## License

This project is for educational purposes. All rights reserved by the authors.
