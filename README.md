# Compare password strength
A C++ code that evaluates and compares the strength of your passwords based on various criteria, including **length**, presence of **digits**, **uppercase**, **lowercase** and **special characters** as well as their **predictable combinations**. <br /><br />
_100% C++, no AI tools used._
## Input and output
__>>__ Takes a **string of passwords** separated by white spaces. <br />
__<<__ Prints out a **comparison table** with the following columns (sorted by score):

<table>
  <tr>
    <td> <b>Score</b> </td>
    <td>Password strength score calculated based on data in the table</td>
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
    <td>Number of special (non-alphanumeric) characters</td>
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
    <td>Common password patterns found</td>
  </tr>
  
</table>

## Common password patterns
The password strength score is negatively affected by the presence of the following predictable patterns:
* Repeated characters (`aaAa`, `----`, `1111`)
* Repeated pairs of characters (`abABab`, `1212`)
* Sequential numbers (`12345`, `7654`)
* Sequential letters (`abcd`, `Dcba`)
* Common words, including keyboard patterns (`WelcoMe`, `Qwerty`)
  
All pattern search algorithms are __case-insensitive__, and the minimum pattern length is set to __{4}__.
## Sample input and output
### Example 1
**Input:** `123123456 123456789 qwerty password 1111111 12345678`<br />
**Output:**<br />
![Comparison table 1](/readme_img/example-1.png)
### Example 2
**Input:** `Iloveyou          Qwertyuiop 1q2w3e4r5t     Dragon ashley1234_____`<br />
**Output:**<br />
![Comparison table 1](/readme_img/example-2.png)
## References
* NordPass. (n.d.). _Top 200 most common passwords._ https://nordpass.com/most-common-passwords-list/
* O’Flaherty, K. (2019, April 21). _These are the world’s most hacked passwords -- is yours on the list?_ Forbes. https://www.forbes.com/sites/kateoflahertyuk/2019/04/21/these-are-the-worlds-most-hacked-passwords-is-yours-on-the-list/?sh=51c56429289c/
