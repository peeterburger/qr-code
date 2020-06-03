## QR-Code Creation

### assumptions

* qr-code version: 		1
* correction level: 	H
* encryption mode:		alphanumeric (0010)
* masking function:		0

### steps
1. generate code
	1. retrieve meta data
			1. retrieve the text to be encoded
			2. select mode (alphanumeric, 0010, 4-bit)
				-> add to binary code
			3. retrieve text length (9-bit)
				-> add to binary code

	2. encode text
		1. split text into two blocks
		2. encode each block
			-> add to binary code
		3. if the binary code is shorter than qr-code
		capacity, fill with 4 ones, or until maximum
		capacity is reached
			-> add to binary code
		4. divide binary code into 8-bit blocks
		5. if the last block is less than 8 bits long,
		fill with 0s
		6. fill the remaining data bits with 11101100
		and 00010001 alternately
		
	3. error correction
		1. convert binary blocks to decimal
		2. calculate number of correction words (17)
		3. calculate reed-solomon-code
			-> add to binary code
		4. convert code back to binary

2. create qr-code matrix
	1. insert fixed patterns
		1. insert position elements
		2. insert timing elements
		3. insert 0-bit (right above lower position element)

	2. insert format information
		1. insert format info from left to right
		2. insert format info from bottom to top

	3. insert binary code (start from bottom right)
		1. for every bit in the binary code, insert into matrix
		and perform mask function on it