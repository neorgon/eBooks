#include <cstdio>
#include <iostream>
#include <exception>
#include <vector>

using namespace std;

#define ENABLE_TEST_1

#define ENABLE_TEST_2

enum class UserRole { ScrumMaster, QE, Dev };

class IUser
{
public:
    virtual ~IUser() { }
    virtual string GetCompleteName() const = 0;
    virtual bool TryToAuthenticate(string userId, string userPassword) = 0;
    virtual UserRole GetRole() = 0;
};

class IIssue
{
public:
    virtual ~IIssue() { }
    virtual IUser * GetAssignee() = 0;
    virtual void SetAssignee(IUser *user) = 0; };

class IIssueTracker
{
public:
    virtual ~IIssueTracker() { }
    virtual IUser * RegisterUser(string ci, string firstName, string lastName, UserRole role, string userId, string userPassword) = 0;
    virtual IUser * Authenticate(string userId, string userPassword) = 0;
    virtual IIssue * RegisterIssue(IUser* user, string title, string description) = 0;
    virtual void ReAssignIssue(IUser *user, IIssue *issue, IUser *newAssignee) = 0; };

class AuthenticationException: public exception {
    string message;

public:
    AuthenticationException(string message)
    {
        this->message = message;
    }

    virtual const char* what() const throw()
    {
        return message.c_str();
    }

    ~AuthenticationException()
    {
    }
};

class PermissionException: public exception {
    string message;

public:
    PermissionException(string message)
    {
        this->message = message;
    }

    virtual const char* what() const throw()
    {
        return message.c_str();
    }

    ~PermissionException()
    {
    }
};

class NotFoundException: public exception {
    string message;

public:
    NotFoundException(string message)
    {
        this->message = message;
    }

    virtual const char* what() const throw()
    {
        return message.c_str();
    }

    ~NotFoundException()
    {
    }
};

class User : public IUser
{
    string ci, firstName, lastName, userId, userPassword;
    UserRole role;

public:
    User(string ci, string firstName, string lastName, UserRole role, string userId, string userPassword)
    {
        this->ci = ci;
        this->firstName = firstName;
        this->lastName = lastName;
        this->role = role;
        this->userId = userId;
        this->userPassword = userPassword;
    }

    string GetCompleteName() const override
    {
        return firstName + lastName;
    }

    bool TryToAuthenticate(string userId, string userPassword) override
    {
        return (this->userId.compare(userId) == 0) && (this->userPassword.compare(userPassword) == 0);
    }

    UserRole GetRole() override
    {
        return role;
    }

    ~User()
    {
    }
};

class Issue : public IIssue
{
    string title, description;
    IUser *assignee;

public:
    Issue(IUser *user, string title, string description)
    {
        assignee = user;
        this->title = title;
        this->description = description;
    }

    IUser * GetAssignee() override
    {
        return assignee;
    }

    void SetAssignee(IUser *user) override
    {
        assignee = user;
    }

    ~Issue()
    {
    }
};

class IssueTracker : public IIssueTracker {
    vector<IUser*> users;
    vector<IIssue*> issues;

    bool VerifyUser(IUser *user)
    {
        for (auto u : users)
        {
            if (u == user)
            {
                return true;
            }
        }
        return false;
    }

    bool VerifyIssue(IIssue *issue)
    {
        for (auto i : issues)
        {
            if (i == issue)
            {
                return true;
            }
        }
        return false;
    }

public:
    IssueTracker()
    {
    }

    IUser * RegisterUser(string ci, string firstName, string lastName, UserRole role, string userId, string userPassword) override
    {
        IUser *user = new User(ci, firstName, lastName, role, userId, userPassword);
        users.push_back(user);
        return user;
    }

    IUser * Authenticate(string userId, string userPassword) override
    {
        for (auto user : users)
        {
            if (user->TryToAuthenticate(userId, userPassword))
            {
                return user;
            }
        }
        throw AuthenticationException("User or password does not match with any registered user.");
    }

    IIssue * RegisterIssue(IUser *user, string title, string description)
    {
        if (!VerifyUser(user))
        {
            throw NotFoundException("User not found in this instance of Issue Tracker.");
        }
        IIssue *issue = new Issue(user, title, description);
        issues.push_back(issue);
        return issue;
    }

    void ReAssignIssue(IUser *user, IIssue *issue, IUser *newAssignee) override
    {
        if (!VerifyUser(user))
        {
            throw NotFoundException("User not found in this instance of Issue Tracker.");
        }
        if (!VerifyIssue(issue))
        {
            throw NotFoundException("Issue not found in this instance of Issue Tracker.");
        }
        if (user->GetRole() != UserRole::ScrumMaster)
        {
            throw PermissionException("Only the scrum master can re assign issues.");
        }
        issue->SetAssignee(newAssignee);
    }

    ~IssueTracker()
    {
        for (auto issue : issues)
        {
            delete issue;
        }

        for (auto user : users)
        {
            delete user;
        }
    }
};

bool test1()
{
#ifdef ENABLE_TEST_1
    bool assertion = false;

    IIssueTracker *issueTracker = new IssueTracker();

    issueTracker->RegisterUser("1234567", "German", "Torrez", UserRole::ScrumMaster, "GermanTorrez", "Password0");
    try
    {
        const IUser *user = issueTracker->Authenticate("GermanTorrez", "Password1");
        user->GetCompleteName();
    }
    catch (exception& e)
    {
        string message = "User or password does not match with any registered user.";
        assertion = message.compare(string(e.what())) == 0;
    }

    delete issueTracker;

    return assertion;
#else
    return false;
#endif
}

bool test2()
{
#ifdef ENABLE_TEST_2
    bool assertion = false;

    IssueTracker concreteIssueTracker;
    IIssueTracker &issueTracker = concreteIssueTracker;

    issueTracker.RegisterUser("1234567", "German", "Torrez", UserRole::ScrumMaster, "GermanTorrez", "Password0");
    issueTracker.RegisterUser("1234568", "Antonio", "Pardo", UserRole::QE, "AntonioPardo", "Password1");
    issueTracker.RegisterUser("1234569", "Julio", "Coca", UserRole::Dev, "JulioCoca", "Password2");

    IUser *dev;
    IUser *scrumMaster;
    IUser *qe;

    try
    {
        dev = issueTracker.Authenticate("JulioCoca", "Password2");
        scrumMaster = issueTracker.Authenticate("GermanTorrez", "Password0");
        qe = issueTracker.Authenticate("AntonioPardo", "Password1");
    }
    catch (exception& e)
    {
        return assertion;
    }

    IIssue *issue = issueTracker.RegisterIssue(qe, "Problem generated when the internet connection is lost.", "Description.");

    try
    {
        issueTracker.ReAssignIssue(qe, issue, dev);
    }
    catch (exception& e)
    {
        string message = "Only the scrum master can re assign issues.";
        assertion = message.compare(string(e.what())) == 0;
    }

    assertion = assertion && issue->GetAssignee()->GetCompleteName().compare(qe->GetCompleteName()) == 0;

    try
    {
        issueTracker.ReAssignIssue(scrumMaster, issue, dev);
    }
    catch (exception& e)
    {
        e.what();
        assertion = false;
    }

    assertion = assertion && issue->GetAssignee()->GetCompleteName().compare(dev->GetCompleteName()) == 0;

    return assertion;
#else
    return false;
#endif
}

class TestSuite
{
    unsigned int passed;
    unsigned int executed;
    unsigned int id;

public:
    TestSuite() : passed(0), executed(0), id(0)
    {
    }

    void run(bool (*test)(), int points)
    {
        bool r = test();
        passed += ((unsigned int) r) * points;
        executed += points;
        ++id;
        const char *result = r ? "PASSED" : "FAILED";
        printf("Test #%d for %d points => %s\n", id, points, result);
    }

    unsigned int getPassed() const
    {
        return passed;
    }

    unsigned int getExecuted() const
    {
        return executed;
    }
};

int main()
{
    TestSuite testSuite;

    testSuite.run(test1, 50);
    testSuite.run(test2, 50);

    printf("FINAL SCORE: %d / %d\n", testSuite.getPassed(), testSuite.getExecuted());

    return 0;
}
