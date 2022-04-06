# 42_minitalk
Sending data one bit at a time.
# Purpose
This project sends signals from a client application to a server application which have to be interpreted to build useable data.
The client uses the server's Program Identifier (PID) to send a message input by the user. The message must be sent using only two signals, meaning
the data must be broken down into binary by the client and then reconstructed by the server before the message is printed.
A document detailing how this can be done [can be found here](https://docs.google.com/document/d/1n99TeyFniUeV-6ENAglxq8JRQCWgpC40umrWS2a1vCk/edit?usp=sharing)

# Bonus
The server must now return a confirmation to the client using the client's PID. The messages sent to the server also need to support Unicode characters.

# Status
Complete! Passes with 125%
