# CSCI-4230-Final-Project

## Establishing secure channel:
ClientHello
ServerHello
ECDSA Certificate
Bank sends ECDHE key to ATM
ServerHello done
ATM sends ECDHE key to Bank
Deriving session keys
ChangeCipherSpec (ATM -> Bank)
ChangeCipherSpec (Bank -> ATM)
