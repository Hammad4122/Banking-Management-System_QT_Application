#ifndef USERSESSIONHANDLER_H
#define USERSESSIONHANDLER_H

#include <QString>
class UserSessionHandler
{
private:
    int userId;
    QString userfirstName;
    QString userlastName;
    QString userfullName = userfirstName + userlastName;
    QString userName;
    QString userEmail;
    QString userMobileNO;
    int userAccountID;
    double userBalance;
    double userIncome;
    double userExpense;

public:
    UserSessionHandler();
    UserSessionHandler(int id, QString firstName,QString lastName,
                       QString username,QString email, QString mobileNo, int accountId, double balance,
                       double income,double expense):

                        userId(id),userfirstName(firstName),userlastName(lastName),userName(username),
        userEmail(email),userMobileNO(mobileNo),userAccountID(accountId), userBalance(balance),
        userIncome(income), userExpense(expense) {};

    // --- Getters ---

    // Return by value for simple types (int)
    int getUserId() const { return userId; }
    int getAccountID() const { return userAccountID; }
    double getBalance() const { return userBalance; }
    double getIncome() const { return userIncome; }
    double getExpense() const { return userExpense; }
    void setBalance(double);

    // Return by const reference for strings (Industry Standard for performance)
    const QString& getFirstName() const { return userfirstName; }
    const QString& getLastName() const { return userlastName; }
    const QString& getUsername() const { return userName; }
    const QString& getEmail() const { return userEmail; }
    const QString& getMobileNo() const { return userMobileNO; }

    // Logic-based getter for Full Name
    QString getFullName() const {
        return userfirstName + " " + userlastName;
    }

};

#endif // USERSESSIONHANDLER_H
