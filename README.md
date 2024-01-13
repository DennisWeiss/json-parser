# json-parser

## Grammar

The grammar from [https://www.json.org/json-en.html](https://www.json.org/json-en.html) has been transformed to be LL(1) parseable. In particular, this means it has no left-recursion and the grammar rule which needs to be applied can be determined by looking at the next character.

```
json
    element

value
    object
    array
    string
    number
    "true"
    "false"
    "null"

object
    '{' members '}'

members
    ""
    member members+

members+
    ""
    ',' members

member
    ws string ws ':' element

array
    '[' elements ']'

elements
    <eps>
    element elements+

elements+
    <eps>
    ',' elements

element
    ws value ws

string
    '"' characters '"'

characters
    ""
    character characters

character
    '0020' . '10FFFF' - '"' - '\'
    '\' escape

escape
    '"'
    '\'
    '/'
    'b'
    'f'
    'n'
    'r'
    't'
    'u' hex hex hex hex

hex
    digit
    'A' . 'F'
    'a' . 'f'

number
    integer fraction exponent

integer
    positive_integer
    '-' positive_integer

positive_integer
    '0'
    onenine digits

digits
    ""
    digit digits

digit
    '0'
    onenine

onenine
    '1' . '9'

fraction
    ""
    '.' digit digits

exponent
    ""
    'E' sign digits
    'e' sign digits

sign
    ""
    '+'
    '-'

ws
    ""
    '0020' ws
    '000A' ws
    '000D' ws
    '0009' ws
```