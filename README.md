# DES Encryption
The Data Encryption Standard is a symmetric-key algorithm for the encryption of digital data.


# How to Use
The key should be represented in 16 bytes hex ascii format example: 0E329232EA6D0D73

The size of the file to be encrypted or decrypted should be a multiple of 64 bytes.
```console
g++ dec.cpp ./des.o
```
To encrypt file. The encryption will be stored as plain text in 'encrypted.txt' and in hex format in 'hex.txt'
 ```console
 ./des.o encrypt ./plain.txt ./key.txt
 ```
 If options are left blank it will default to the previous values
 ```console
 ./des.o
 ```
 To decrypt file. The decryption will be stored in 'decrypted.txt'
 ```console
 ./des.o decrypt ./plain.txt ./key.txt
 ```
