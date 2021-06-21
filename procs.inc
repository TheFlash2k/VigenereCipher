; Procedure for Printing the menu and reading data from user
; and storing to uChoice variable.
PrintMenu PROC
	MOV EDX, OFFSET menu_0
	CALL WriteString
	CALL CRLF
	MOV EDX, OFFSET menu_1
	CALL WriteString
	CALL CRLF
	MOV EDX, OFFSET menu_2
	CALL WriteString
	CALL CRLF
	ret
PrintMenu ENDP
; Procedure to print information about the project
; and the group members
PrintInfo PROC
	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET PROJ_NAME
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET PROJ_LANG
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF
	
	; Printing details about group members.
	MOV EDX, OFFSET GP_0
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET GP_1
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET GP_2
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET GP_3
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET GP_4
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF

	ret ; Returning from procedure

PrintInfo endp
; Procedure for Reading Key from the user.
ReadCipherKey PROC
		; Printing a seperator
		MOV EDX, OFFSET Seperator
		CALL WRITESTRING
		CALL CRLF
	Init:
		; Printing Message for key
		MOV EDX, OFFSET get_key
		CALL WriteString
		; Reading key from user
		MOV EDX, OFFSET key
		MOV ECX, MAX_LEN - 1
		CALL ReadString

	; Converting the key to uppercase:
	INVOKE str_ucase, ADDR Key

	; Getting the length of key:
	INVOKE str_length, ADDR key
	; EAX will now contain the length of the key
	; Moving that to our len_key variable
	MOV len_key, EAX

	;; Checking if the key contains any spaces or numbers:
	MOV ESI, 0
	MOV ECX, len_key
	iter:
		;; Checking for space:
		MOV EAX, 0
		MOVZX EAX, key[ESI]

		CMP EAX, 20h ; Space in hex (asciitable.com)
		JE Invalid

		;; Checking for numbers
		;; The way we check is if the value is < 65 and >= 91
		CMP EAX, 65d ;; -> 65d = 'A'
		JL Invalid

		CMP EAX, 91d ;; -> 65d = 'A'
		JGE Invalid

		;; Incrementing and decrementing values
		INC ESI
		DEC ECX
		;; Checking for end of loop.
		CMP ECX, 0
		JE Return
		JMP iter
	Invalid:
		MOV EDX, OFFSET incorr_key
		CALL WriteString
		CALL CRLF
		JMP Init
	Return:
		;; Adding null byte to the end of the key:
		MOV ESI, len_key
		INC ESI ;; i++
		MOV key[ESI], 0h ;; 0x00 -> NullByte
		RET
ReadCipherKey ENDP
; Procedure for Reading Cipher Text from the user
; For decryption method
ReadCipherText PROC
	; Printing a seperator
	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF

	; Printing Message for key
	MOV EDX, OFFSET get_c_text
	CALL WriteString
	
	; Reading key from user
	MOV EDX, OFFSET cipherText
	MOV ECX, MAX_LEN - 1
	CALL ReadString

	; Converting the text to uppercase:
	INVOKE str_ucase, ADDR cipherText

	; Getting the length of text:
	INVOKE str_length, ADDR cipherText
	MOV len_cipher, EAX

	ret
ReadCipherText ENDP
; Procedure for Reading Plain Text from the user
; For encryption method
ReadPlainText PROC
	; Printing a seperator
	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF
	; Printing Message for key
	MOV EDX, OFFSET get_p_text
	CALL WriteString
	
	; Reading key from user
	MOV EDX, OFFSET plainText
	MOV ECX, MAX_LEN - 1
	CALL ReadString

	; Converting the text to uppercase:
	INVOKE str_ucase, ADDR plainText

	; Getting the length of text:
	INVOKE str_length, ADDR plainText
	MOV len_plain, EAX

	ret
ReadPlainText ENDP
; Procedure for getting the menu choice that will
; be either encryption or decryption
GetChoice PROC
	; Just a random check, if eax is set to 0, we will not print error message
	; if it is not 0, we will know an invalid value has been entered and
	; we will print that error.
	; C+ level code:
	; cout << "Enter choice: ";
	; cin >> choice;
	; while(choice != 0 && choice != 1)
	; { cout << "Invalid choice. Only choose 1 or 2.\nEnter choice: ";
	; cin >> choice; }
	MOV EAX, 0
	Begin:
		CMP EAX, 0
		JE Start
		MOV EDX, OFFSET err_invalid_choice
		CALL WriteString
		CALL CRLF
	Start:
		MOV EDX, OFFSET msg_choice
		CALL WriteString
		; Reading choice from user:
		; MOVING EAX TO 0 because ReadInt reads
		; data from user in EAX.
		MOV EAX, 0
		CALL ReadInt
		; Verifying if a valid key was entered:
		CMP EAX, 1
		JNE invalid
		; Moving data from EAX to variable 
	Valid:
		MOV uChoice, EAX
		JMP Return
	Invalid:
		; Validating again if key entered was 2. Because we already did check for 1
		CMP EAX, 2
		JE Valid ; Jump if equal to valid
		MOV EAX, 5 ; Setting eax to 1 to bypass our condition and print error
		JMP Begin
	Return:
		ret
GetChoice ENDP
; Procedure that will print the final values
PrintFinal PROC
	; Printing a seperator
	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF
	
	; Printing the key
	MOV	EDX, OFFSET KEY_IS
	CALL WRITESTRING
	MOV  EDX, OFFSET KEY
	CALL WRITESTRING
	CALL CRLF
	; Printing the encrypted text
	MOV EDX, OFFSET ENC_IS
	CALL WRITESTRING
	MOV EDX, OFFSET cipherText
	CALL WRITESTRING
	CALL CRLF
	; Printing the decrypted text
	MOV EDX, OFFSET DEC_IS
	CALL WRITESTRING
	MOV EDX, OFFSET plainText
	CALL WRITESTRING
	CALL CRLF
	; Printing a seperator
	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF

	;; Checking if the user wants to store the data into the file:
	CALL checkWrite

	; Printing a seperator
	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF

	ret
PrintFinal ENDP
; Procedure to equate the key to the length of the cipher/plain text:
BuildKey PROC

	MOV EBX, len_key ;; Moving the length of key to EBX
	CMP EAX, 2 ;; Checking if EAX is 2, then jumping to checking
	;; if length of cipher is greater than the key or not
	;; If it's greater or equal, simply returning
	JE isDecrypt

	isEncrypt:
		MOV EDX, len_plain
		CMP EBX, len_plain
		JGE Return
		JMP Build

	isDecrypt:
		MOV EDX, len_cipher
		CMP EBX, len_cipher
		JGE Return

	Build:
		;; Main Label to build the 
		;; Copying our key into another variable:
		INVOKE str_copy, ADDR key, ADDR cp_key
		
		MOV EBX, EDX
		; MOV EAX, EBX
		; call writedec
		; call crlf
		; call waitmsg

		;; Setting Stack Index to 0
		MOV ESI, 0
		;; Setting the EDI to the length of the original key + 1
		MOV EDI, len_key
		;; Setting a random A value
		;; Doing this because at that particular index, there exists a nullbyte,
		;; so overwriting taht null byte.
		MOV ECX, len_key
		MOV key[EDI], 65d
		;; Iterating over the copied string and checking the length:
	FOR_LOOP:
		;; Emptying EAX so that we can store our own value in there.
		MOV EAX, 0
		;; Copying the first index
		MOV AL, cp_key[ESI]
		;; Adding the value of cp_key to the end of the key
		MOV key[EDI], AL
		;; Incrementing and decrementing values
		INC ESI
		INC EDI
		DEC ECX
		;; Again comparing if the length of key
		;; and plain/cipher text is the same:
		;; Calulating the length of the current key:
		INVOKE str_length, ADDR key ;; return value in eax
		;; Checking if the loop has ended i.e. i==0
		;; then we check if the key is equal to plain text
		;; if not, we re-iterate.
		CMP ECX, 0
		JE ReCheck
		;; Checking if the key has been matched without the loop reaching its end
		;; so we simply go to the label that adds a null-byte
		CMP EAX, EBX
		JE ADD_NULL
		;; Unconditional jump to the beginning of loop
		JMP FOR_LOOP
	ReCheck:
		CMP EAX, EBX
		JE ADD_NULL
		;; Resetting the variables to point to the first char in the string that 
		;; is to be copied and then 
		MOV ECX, LEN_KEY
		MOV ESI, 0
		MOV EDI, EAX
		JMP FOR_LOOP
	ADD_NULL:
		;; Checking if the user chose decrypt, then we increment edi before
		;; adding a null byte, if not, simply adding null byte and returning.
		CMP uChoice, 2
		JE INC_EDI
	_NULL_:
		MOV key[EDI], 0H
	Return:
		ret
	INC_EDI:
		INC EDI
		JMP _NULL_
BuildKey ENDP
;;; -> MAIN Procedure that performs all the encryption.
Encrypt PROC
	;; Setting values to 0:
	MOV ESI, 0
	MOV ECX, 0
	;; Iterating over the entire string:
	;; MOV ECX, len_plain ; int i = x
	MOV EAX, len_plain
	MOV curr_len, EAX

	for_loop:
		MOV EAX, 0 ; -> x = 0
		MOV EBX, 0 ; -> y = 0
		MOV EDX, 0 ; -> FOR DIV
		MOV EDI, 0
		;; x = plainText[i];
		MOVZX EAX, plainText[ESI]
	RESET:
		;; y = key[i];
		MOVZX EDI, key[ECX]
		;; Comparing if plainText contains a space, adding it and then
		;; Moving to the next iteration
		CMP EAX, 20h ;; 0x20 -> Space ASCII in hex
		JE AddSymbol
		;; Comparing numbers now (Same as done in key)
		CMP EAX, 65d ;; 'A'
		JL AddSymbol
		;; All those numbers greater than 90d
		CMP EAX, 90d ;; 'Z'
		JG AddSymbol
		;; char z = x + y;
		ADD EAX, EDI
		;; As there are 26 alphabets in the dictionary
		;; limiting to 26 using -> EAX MOD 26
		MOV EBX, 26
		DIV EBX
		MOV EAX, EDX ; EDX contains the remainder
		;; Now, since in ASCII, alphabets start from 65
		;; (Because we're using uppercase alphabets)
		ADD AL, 65 ;; Adding 65 to the lower 8 bit register.
		;; Storing the data into the cipherText
		MOV cipherText[ESI], AL ;; cipherText[i] = <value>
		JMP Ret_Loop
	AddSymbol:
		;; This label will simply copy any non-alphabet back into the array without making
		;; modifications or anything from the algorithm
		MOV EAX, 0
		MOV AL, plainText[ESI]
		MOV cipherText[ESI], AL
		MOV EAX, 1
		JMP Ret_Loop
	INC_ECX:
		INC ECX
		JMP ReCheck
	Ret_Loop:
		;; Decrement -> i--
		DEC curr_len
		;; ESI++
		INC ESI
		CMP EAX, 1
		JNE INC_ECX
		;; if(ECX == 0) break;
	ReCheck:
		CMP curr_len, 0
		JE RETURN
		JMP for_loop
	RETURN:
		;; Adding null byte to the end of the ciphertext:
		MOV cipherText[ESI], 0h ;; 0x00 -> NULL BYTE
		ret
Encrypt ENDP
;;; -> MAIN Procedure that performs the decryption.
Decrypt PROC

	MOV ESI, 0
	MOV ECX, 0
	MOV EAX, len_cipher ;; Setting loop counter to the length of the cipher
	MOV curr_len, EAX
	for_loop:
		MOV EAX, 0 ; -> x = 0
		MOV EBX, 0 ; -> y = 0
		MOV EDX, 0 ; -> FOR DIV
		MOV EDI, 0
		;; x = cipherText[i];
		MOVZX EAX, cipherText[ESI]
	RESET:
		;; y = key[i];
		MOVZX EDI, key[ECX]
		;; Comparing if plainText contains a space, adding it and then
		;; Moving to the next iteration
		CMP EAX, 20h ;; 0x20 -> Space ASCII in hex
		JE AddSymbol
		;; Comparing numbers now (Same as done in key)
		CMP EAX, 65d ;; 'A'
		JL AddSymbol
		;; All those numbers greater than 90d
		CMP EAX, 90d ;; 'Z'
		JG AddSymbol
		;; ====================================
		;;				ACTUAL CODE
		;; ====================================
		;; As there are 26 alphabets in the dictionary
		;; limiting to 26 using -> EAX MOD 26
		;; char z = x - y;
		SUB EAX, EDI
		ADD EAX, 26
		MOV EBX, 26
		DIV EBX
		MOV EAX, EDX ; EDX contains the remainder
		;; Now, since in ASCII, alphabets start from 65
		;; (Because we're using uppercase alphabets)
		ADD AL, 65 ;; Adding 65 to the lower 8 bit register.
		;; Storing the data into the cipherText
		MOV plainText[ESI], AL ;; cipherText[i] = <value>
		JMP Ret_Loop
	AddSymbol:
		;; This label will simply copy any non-alphabet back into the array without making
		;; modifications or anything from the algorithm
		MOV EAX, 0
		MOV AL, cipherText[ESI]
		MOV plainText[ESI], AL
		MOV EAX, 1
		JMP Ret_Loop
	INC_ECX:
		INC ECX
		JMP ReCheck
	Ret_Loop:
		;; Decrement -> i--
		DEC curr_len
		;; ESI++
		INC ESI
		CMP EAX, 1
		JNE INC_ECX
	ReCheck:
		;; if(ECX == 0) break;
		CMP curr_len, 0
		JE RETURN
		JMP for_loop
	RETURN:
		;; Adding null byte to the end of the ciphertext:
		MOV plainText[ESI], 0h ;; 0x00 -> NULL BYTE
		ret
Decrypt ENDP
;; Do While Loop in c++ that tests if the user wants a rego
;; or not.
ReGo PROC

		MOV EAX, 0
		MOV EDX, OFFSET get_rego
		CALL WriteString
	BEGIN:
		CALL ReadChar
		CALL WriteChar ;; Printing the read char onto the screen
		CALL CRLF
		;; Moving the value of lower register to reGoChoice
		MOV reGoChoice, AL
		;; Converting the read value to uppercase:
		XOR reGoChoice, 00100000b

		;; Checking if the user entered a value besides
		;; Y or N
		;; FOR Y:
		CMP reGoChoice, 89d ;; 89 -> 'Y'
		JE _END
		;; FOR N:
		CMP reGoChoice, 78d ;; 78 -> 'N'
		JE _END
		;; Any other value entered would be considered invalid.
		MOV EDX, OFFSET err_inv_regoChoice
		CALL WriteString
		JMP BEGIN ;; Direct jump to the begin label
	_END:
		ret
ReGo ENDP
;; This procedure clears all the pre-allocated memory
CLEAR_EVERYTHING PROC
	;; Clearing Variables:
	XOR EAX, EAX ;; Empyting EAX
	MOV len_key, EAX
	MOV len_cp_key, EAX
	MOV len_cipher, EAX
	MOV len_plain, EAX
	MOV curr_len, EAX
	MOV reGoChoice, AL
	MOV uChoice, EAX
	MOV pHolder, EAX
	MOV fileHandle, EAX
	MOV bytesRead, EAX
	;; Clearing Arrays:
	;;;; KEY
	MOV ECX, SIZEOF key
	MOV EDI, OFFSET key
	CLD
	REP STOSB
	;;;; CP_KEY
	MOV ECX, SIZEOF CP_KEY
	MOV EDI, OFFSET CP_KEY
	CLD
	REP STOSB
	;;;; PlainText
	MOV ECX, SIZEOF plainText
	MOV EDI, OFFSET plainText
	CLD
	REP STOSB
	;;;; CipherText
	MOV ECX, SIZEOF cipherText
	MOV EDI, OFFSET cipherText
	CLD
	REP STOSB
	;;; fileData
	MOV ECX, SIZEOF fileData
	MOV EDI, OFFSET fileData
	CLD
	REP STOSB
	;;;; fileName
	MOV ECX, SIZEOF fileName
	MOV EDI, OFFSET fileName
	CLD
	REP STOSB
	;; Clearing registers
	XOR EAX, EAX
	XOR EBX, EBX
	XOR ECX, ECX
	XOR EDX, EDX
	XOR EDI, EDI
	XOR ESI, ESI

	ret
CLEAR_EVERYTHING ENDP
;; Procedure to check if user wants to read data from file or not:
checkReadFile PROC
	; Printing a seperator
	MOV EDX, OFFSET Seperator
	CALL WRITESTRING
	CALL CRLF

	MOV EDX, OFFSET msg_read
	CALL WriteString
	;; Emptying EAX as char has to be read in eax
	MOV EAX, 0
	Input:
		CALL ReadChar
		CALL WriteChar
		CALL CRLF
		;; Converting char to uppercase
		XOR al, 00100000b

		CMP al, 89d ;; 89 -> 'Y'
		JE _True
		;; FOR N:
		CMP al, 78d ;; 78 -> 'N'
		JE _END
		;; Any other value entered would be considered invalid.
		MOV EDX, OFFSET err_inv_regoChoice
		CALL WriteString
		JMP Input ;; Direct jump to the begin label
	_True:
		CALL READ_FROM_FILE
	_END:
		ret
checkReadFile ENDP
;; Data that is to be read from file:
READ_FROM_FILE PROC
	MOV EDX, OFFSET msg_file
	CALL WriteString
	BEGIN:
		MOV EDX, OFFSET FileName
		MOV ECX, SIZEOF FileName
		CALL ReadString

		;; Opening File
		CALL OpenInputFile
		MOV fileHandle, EAX
		;; Checking if file exists or not:
		CMP EAX, INVALID_HANDLE_VALUE
		JNE Read
		MOV EDX, OFFSET err_file_not_exist
		CALL WriteString
	Invalid:
		CALL ReadInt
		CMP EAX, 1
		JE BEGIN
		CMP EAX, 2
		JE _END
		MOV EDX, OFFSET err_invalid_choice
		JMP Invalid
	Read:
		;; Actual label where data is read from file:
		PUSH EAX
		MOV EDX, OFFSET fileData
		MOV ECX, MAX_LEN
		CALL ReadFromFile
		POP EAX
		CALL CloseFile
		;; Copying read data to either cipher text variable or plain text one.
		MOV EDX, OFFSET fileData
		CMP uChoice, 1
		JE toEncrypt
		JMP toDecrypt
	toEncrypt:
		INVOKE str_copy, ADDR fileData, ADDR plainText
		INVOKE str_ucase, ADDR plainText
		INVOKE str_length, ADDR plainText
		MOV len_plain, EAX
		JMP DIR_EXIT
	toDecrypt:
		INVOKE str_copy, ADDR fileData, ADDR cipherText
		INVOKE str_ucase, ADDR cipherText
		INVOKE str_length, ADDR cipherText
		MOV len_cipher, EAX

		JMP DIR_EXIT
	_END:
		MOV EAX, 0
		ret
	DIR_EXIT:
		MOV EAX, 1
		ret
READ_FROM_FILE ENDP
checkWrite PROC
	MOV	EAX, 0
	MOV EDX, OFFSET write_out
	CALL WriteString
	Begin:
		CALL ReadChar
		CALL WriteChar
		CALL CRLF

		;; Converting to uppercase:
		XOR AL, 00100000b

		CMP AL, 89d ;; 89 -> 'Y'
		JE _Write
		;; FOR N:
		CMP AL, 78d ;; 78 -> 'N'
		JE _END

		;; Invalid Value:
		MOV EDX, OFFSET err_inv_regoChoice
		CALL WriteString
		JMP Begin
	_Write:
		CALL WRITE_TO_FILE
	_END:
		ret
checkWrite ENDP
WRITE_TO_FILE PROC
	
	CMP uChoice, 1
	JE EncryptLbl
	JMP DecryptLbl

	EncryptLbl:
		INVOKE str_copy, ADDR out_encrypt, ADDR fileName
		INVOKE str_copy, ADDR cipherText, ADDR fileData
		JMP _Writer
	DecryptLbl:
		INVOKE str_copy, ADDR out_decrypt, ADDR fileName
		INVOKE str_copy, ADDR plainText, ADDR fileData
	_Writer:
		;; Now we only have to deal with 1 file having the output
		;; name in "fileName" variable.
		;; -> Creating the file first:

		INVOKE str_length, ADDR fileData

		MOV EDX, OFFSET fileName
		CALL CreateOutputFile
		;; Writing data onto the file:
		PUSH EAX
		MOV EDX, OFFSET fileData
		MOV ECX, EAX
		CALL WriteToFile
		POP EAX
		CALL CloseFile

	CMP uChoice, 1
	JE WriteEncrypt
	JMP WriteDecrypt

	WriteEncrypt:
		MOV EDX, OFFSET data_wr_ci
		CALL WriteString
		MOV EDX, OFFSET out_encrypt
		CALL WriteString
		CALL CRLF
		JMP _RET
	WriteDecrypt:
		MOV EDX, OFFSET data_wr_pl
		CALL WriteString
		MOV EDX, OFFSET out_decrypt
		CALL WriteString
		CALL CRLF
	_RET:
		ret
WRITE_TO_FILE ENDP