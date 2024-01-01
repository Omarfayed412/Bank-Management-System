# CSE126 Final Project

## About the Repo
This repo contains the code for Bank Management System written in C.
This program will create and maintain a Bank management system to keep track of Accounts inside the bank.
Each Account has an account number, name, mobile, email address, balance, and date opened(another struct of month and year).
We have written this code following naming conventions and clean code concepts to make the code work in an optimized and efficient way. Many approaches have been followed to apply optimization techniques to reduce memory consumption and decrease the time complexity.
We also put into consideration the security standards that may keep our program immune to cyberthreats and vulnerabilities.

## Program Flow & Functions
Throughout this section you’ll get a clear overview over the
implementation of the functions in this program.
Before we start diving into the program let’s get a general overview on the data and database. The data of the users and accounts is saved within a text file containing the data cells with a comma separating
each cell.
### A. Logging in
First step of our program is logging in for the employees stored within the file users.txt. The program creates an array of structs for users with a password and username. The function readUser() is called to open the file and read the data stored in it and store it in the array of stucts of users.
After then, the login() function takes place by checking the entered username and password matches the ones stored in the database.
### B. Loading Data:
After a successful login the program calls loadAccounts() which should start loading the data of the accounts stored inside the accounts.txt file. By applying this method we can ensure that the data wont be retrieved if the user is not authorized which applies the concept of least privilege. The function stores the data in an array of structs of type
Account. Main algorithm goes by reading a line from the file then passeing this line to strtok() which separates the line according to the comma delimiter. Each time the initial token starts a series of tests is done to assign all the strcut attributes until the token equal NULL.
Everytime the function fgets() reads a line it adds one to the acCounts which is a global variable that holds number of
accounts.
### C.Main Menu:
After loading the data of the accounts stored in the database
we move to the actual program. The program calls Menu()
function which is the main routine of the program. It contains
a while loop that holds the whole program options within. It
asks the user to enter the option desired then the users is
required to enter the name of the option as shown on the
screen. The menu acts as a CLI it takes a string and
converts it to upper case using StrToUpper() function which
makes all the string characters in upper case. We choosed
this approach to make the program not case sensitive so the
user is able to enter the option in any case they want.
According to the chosen operation the function calls the
operation function then after the function ends and is popped
off from the stack it returns to the while loop of the Menu().
D.Adding Users:
So the first operation we got is the Add() which adds a user
to the database. The function asks the user to enter a valid
account number and it keeps asking the user until they enter
an account number that doesn’t exist in the database and is
valid. A valid account number is checked by
checkAccountNo() which returns 1 if valid ;otherwise, it
returns 0. A vild account number means it has a length of
10-digits and doesn’t contain any letters or special
characters. The existence check is done using
AccountExistenceCheck() which returns 0 if it exists by
looping through all the account numbers stored in the array
of structs. After a valid account number is entered the mobile
number is required. Checking on the mobile number is done
using checkNumber() which returns 1 if valid. A valid
mobile number contains 11-digits without any characters.
After entering all valid data function asks you if you want to
save ,you can either choose yes or no. After that, You;re
asked if you want to add more accounts without returning to
main. After adding the account the accounts counter
increases by one and the data entered is assigned to the
object located in the array of structs. You have to notice that
when a new account is added its balance is set to 0.0 by
default. The function sets the date of the account opened as
the current date using the time() function which returns time
in seconds since 1970 and then the output is formalized
using the function locate().
E. Deleting Users:
This operation gives the user the privilege to delete an
account but this account must have zero balance. The ideo
of the function Delete() is locating the account number to be
deleted after it checks it for validity, existence and balance.
After locating the account by using locateAccount() function
it swaps the struct saved in this index in the array of structs
with the next account until it makes it at the end of the
accounts in the array. After then, It decrements the acCount
which holds the number of accounts. So the next account to
be added will overwrite the data of that account to be deleted
and even if there wasn’t an account to be added the function
Save() will save all the account except it.
F. Modifying Data:
Our program supports modifying your data by calling
Modify() function but only the User name, Mobile number
and email address. It has the same scenario as Add(),
checks account number then gives you the options to modify
the desired data. The function calls loadAccIndex() function
which returns the index of the given account number. You
can save the new data by typing Y or y when you’re asked.
You have the ability to modify other accounts without
returning to main.
G.Transfering Money:
Let’s get more Financial! You can transfer an amount of
money not exceeding 10000$ per transaction by calling the
function Transfer(). This function asks you to enter the
sender and receiver account numbers, Performs validation
and existence checks. It asks you to enter the amount of
money to be transferred which has to be numbers only and
smaller than or equal your balance. It uses also the function
loadAccIndex() to locate the two accounts, add the amount
to reciever balance and subtract it from sender balance.
After the transaction it asks you whether you want to save or
not same as mentioned before. Whenever you do any
transaction a file with the account number as its name is
created as a history log for your operations. You can transfer
money again without returning back to the main.
H.Depositting Money:
Same as Transfer() but it calls Deposit() function which
takes one account number. It has the same restrictions as
transfer in terms of max amount per transaction. You can
save or not as the rest and repeat the operation if you want
to. Remember that a file with its name same as the account
number is created containig the history of your transactions.
I. Withdrawing Money:
Same as Deposit() but it calls Withdraw() function which
takes one account number. It has the same restrictions as
transfer in terms of max amount per transaction. You can
save or not as the rest and repeat the operation if you want
to. Remember that a file with its name same as the account
number is created containig the history of your transactions.
J. Searching:
This operation calls Query() Which asks you for an account
number then checks its validity. It searches in the database
usnig loadAccIndex() for this account number then calls
function printUser() which prints all the information about a
specific user. You can perform the same operation again
without returning to main as the rest of operations.
K. Advanced Searching:
This function enables the user to search in the database of
user names with any keyword then it prints all the users with
matching pattern of strings. It uses strstr() function to do this
job of searching for the pattern given as keyword inside the
strings of the usernames. It converts the keyword into upper
case using StrToUpper() function and does the same with
usernames in the array of structs so that it can handle case
sensitivity. After it finds the matching results it calls the funct
printUser() to print all users with matching results. You can
repeat the process like the rest for sure.
L. Printing & Sorting:
This functions is the User Joker card. The function Sort()
prints out all the accounts in the database in sorted way
according to two factors. The first factor is wheter you want
sortByName() or sortByBalance or sortBydate() and the
second factor is whether you want it to be printed in
ascending or descending order. We used the Bubble sort
algorithm in the thress methods of sorting. For example, the
sortByName() uses strcmp() to compare the user names
saved and swap them according to order choosed. Same
goes with sortByBalance() and SortByDate(). When sorting
by date we compare the years first then we compare
months. After swapping the indecies of the elements we
assign these indices in a temporary array so that we can
loop throught this array of indecies and use printUser() to
print the users in the order of indecies are sorted. The
temporary array is created using the fubction fillArray()
which reserves a place in the mamory using malloc() and fill
it with numbers from 0 to acCount -1.
M.Report for Transactions:
By calling Report() function it opens the text file of an
entered and checked account number from the user then it
prints out the last 5 transactions stored in the file named by
account number. It counts number of lines of the file of
history then subtracts 5 from it to start from the last five lines
then it calls the function fseek() to return to the start of the
file to count from the beginning. You can repeat this
operation too.
N.User Manual:
Holds the user manual data and prints it on screen to help
the user on how to deal with the program. It includes all the
operations allowed for users and restrictions of input data.
O.Saving Data:
We have mentioned the function Save() nearly in all the
operation that can change data in the database. This
function takes out all the data stored with the array of strcuts
and print it in the same order of cells as it was retrieved at
the begging of the program. It uses fprintf() and fopen() to
open the accounts.txt file

## Contributors
- [Omar Fayed](https://www.github.com/Soupaul)
- [jomanaehabb](https://github.com/jomanaehabb)
- [YaseenIslam2005](https://github.com/YaseenIslam2005)
- [AmrZeina](https://github.com/AmrZeina)
