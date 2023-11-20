# Blood Bank Management System -BBMS

The Blood Bank Management System is a simple console-based application that allows users to register, log in, and perform various operations related to blood donors.

## Project Team

- Md Tanvir Hasan Tonmoy (221-15-5200)
- Md Shoaib Ahmed (221-15-4955)
- Anik Islam Rafi (221-15-5407)

## Features

1. **User Registration:**
   - Users can register with a unique username and password.
   - Donor information, including name, blood type, and age, is collected during registration.

2. **User Login:**
   - Registered users can log in using their username and password.

3. **Display Donors:**
   - After logging in, users can view a list of registered blood donors.

4. **Search Donors:**
   - Users can search for donors based on blood type or donor name.

5. **Logout:**
   - Users can log out of the system to ensure the security of their accounts.

6. **Delete User:**
   - Logged-in users have the option to delete their accounts, automatically logging them out.

## Usage

1. **Registration:**
   - Choose option 1 to register a new user.
   - Enter the required details, including username, password, donor name, blood type, and age.

2. **Login:**
   - Choose option 2 to log in.
   - Enter your username and password when prompted.

3. **Display Donors:**
   - Choose option 4 to display a list of registered donors.

4. **Search Donors:**
   - Choose option 5 to search for donors by blood type or donor name.

5. **Logout:**
   - Choose option 8 to log out of the system.

6. **Delete User:**
   - Choose option 9 to delete the logged-in user's account.

7. **Exit:**
   - Choose option 11 to exit the program.

## Building and Running

Compile the program using a C compiler:

```bash
gcc blood_bank.c -o blood_bank
