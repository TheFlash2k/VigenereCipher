INCLUDE Irvine32.inc
INCLUDE MACROS.inc
.data
	; Reading all the variables from the file.
	INCLUDE vars.inc
.code
	; Including other procedures from Procs.inc
	; Similar to creating another header file
	; and including using "#include "header.h"
	INCLUDE Procs.inc
main PROC
	Start:
		CALL CLRSCR ;; Invoking the clear screen procedure.
		; Printing Details about the project
		CALL PrintInfo
		; Printing the menu
		CALL PrintMenu
		; Reading data from user
		; and storing to uChoice variable.
		CALL GetChoice
		; Reading the key from the user
		CALL ReadCipherKey
		; Checking if user wants to read data from a file:
		CALL checkReadFile
		;; The return value will be stored in EAX, if the value is 1,
		;; that means the user read data from and data has been stored
		;; in the respective variables.
		CMP EAX, 1
		JE After
		; Comparing whether the user chose to encrypt (1) a message
		; or decrypt (2)
		CMP uChoice, 1
		JE Encryption
		; If this fails, we already know it could
		; either be 1 or 2, so simply
		; we will fall into the decryption block
	Decryption:
		CALL ReadCipherText
		JMP After
	Encryption:
		CALL ReadPlainText
		JMP After
	setPlainLen:
		JMP Exec
	After:
		; Moving size of  plain/cipher text to EAX
		; and offset of Key to EDX to make it 
		; equal to the size of the text.
		;; Checking if the choice was 1 then setting EAX to length of plaintext
		;; else setting it to the cipher text.
		CMP uChoice, 1
		JE setPlainLen
	Exec:
		MOV EAX, uChoice ;; Moving the user choice into EAX, this will allow us to check 
		;; for the choice in BuildKey procedure.
		CALL BuildKey
		CMP uChoice, 1
		JE callEncrypt
		CALL Decrypt
		JMP CheckRe
	callEncrypt:
		CALL Encrypt
	CheckRe:
		CALL PrintFinal
		CALL ReGo
		;; Comparing if the user wants to rego or not:
		CMP reGoChoice, 89d ;; 'Y'
		JE Restart
		JMP _END
	Restart:
		CALL CLEAR_EVERYTHING
		JMP Start
	_END:
		;;================================
		MOV EDX, OFFSET Seperator
		CALL WriteString
		CALL CRLF
	exit
main ENDP
END main