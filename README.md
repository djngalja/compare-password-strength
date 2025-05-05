# Compare password strength
A C++ code that evaluates and compares the strength of your passwords based on various criteria, including **length**, presence of **digits**, **uppercase**, **lowercase** and **special characters** as well as their **predictable combinations**. <br /><br />
_100% C++, no AI tools used._
## Input and output
Takes a **string of passwords** separated by white spaces. <br /><br />
Prints out a **comparison table** with the following columns (sorted by score):

<table>
  <tr>
    <td> <b>Score</b> </td>
    <td>Password strength score calculated based on the data in the table</td>
  </tr>
  
  <tr>
    <td><b>Password</b></td>
    <td>Password entered by the user</td>
  </tr>
  
  <tr>
    <td><b>Length</b></td>
    <td>Password length</td>
  </tr>

  <tr>
    <td><b>SP Chars</b></td>
    <td>Number of special (not alphanumeric) characters</td>
  </tr>

  <tr>
    <td><b>Digits</b></td>
    <td>Presence of digits</td>
  </tr>

  <tr>
    <td><b>LCase</b></td>
    <td>Presence of lowercase characters</td>
  </tr>

  <tr>
    <td><b>UCase</b></td>
    <td>Presence of uppercase characters</td>
  </tr>

  <tr>
    <td><b>Patters</b></td>
    <td>Presence of common password patterns</td>
  </tr>
  
</table>

## Common password patterns
* Repeated characters (`aaAa`, `----`, `1111`)
* Repeated pairs of characters (`abABab`, `1212`)
* Consecutive numbers (`12345`, `7654`)
* Letters in (reverse) alphabetical order (`abcd`, `Dcba`)
* Common words or phrases (`WeLcoMe`, `computer`)
  
The pattern search algorithm is case-insensitive.
## Sample input and output
### Example 1
**Input:** `ADmINadmin PA$$w0rD1234 QWERTY007 password`<br />
**Output:**<br />
![Comparison table 1](/readme_img/table1.jpg)
### Example 2
**Input:** `AbcdEf76543        3456ZYxW   `<br />
**Output:**<br />
![Comparison table 1](/readme_img/table2.jpg)
### Example 3
**Input:** `1111PasssworD    hahahaHA678 hi+++++bye 565656StoP____ `<br />
**Output:**<br />
![Comparison table 3](/readme_img/table3.jpg)
### References
* NordPass. (n.d.). _Top 200 most common passwords._ https://nordpass.com/most-common-passwords-list/
