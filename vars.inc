; Variables for Project Details
PROJ_NAME BYTE "Vignere Cipher - Encryption Decryption.", 0
PROJ_LANG BYTE "In x86 Assembly using Irvine Library", 0
Seperator BYTE "========================================", 0

; Variables for group details printing:
GP_0 BYTE "PROJECT BY: ", 0
GP_1 BYTE "===================================", 0
GP_2 BYTE "@TheFlash2k | Discord : TheFlash2k#0407", 0
GP_3 BYTE "https://github.com/theflash2k", 0
GP_4 BYTE "===================================", 0

; Messages that have to be printed:
menu_0	   BYTE "== MENU ==", 0
menu_1     BYTE "1. Encrypt.", 0
menu_2     BYTE "2. Decrypt.", 0
msg_choice BYTE "Enter choice: ", 0
get_key    BYTE "Enter the key: ", 0
get_c_text BYTE "Enter the cipher text for decryption: ", 0
get_p_text BYTE "Enter the plain text for encryption: ", 0
get_rego   BYTE "Do you want to continue? (Y/N): ", 0
msg_read   BYTE "Do you want to read from file? (Y/N): ", 0
msg_file   BYTE "Enter the file name: ", 0
write_out  BYTE "Do you want to write the output to file? (Y/N): ", 0
data_wr_ci BYTE "Encrypted text stored to file ", 0
data_wr_pl BYTE "Decrypted text stored to file ", 0

; Message variable for errors:
incorr_key         BYTE "Key can only contain alphabets not spaces or any other symbols/numbers.", 0
err_invalid_choice BYTE "Invalid Choice. Only choose 1 or 2...", 0
err_inv_regoChoice BYTE "Invalid Choice. Type either 'Y' or 'N': ", 0
err_file_not_exist BYTE "File doesn't exist. Do you want to read another file or exit? (1 or 2): ", 0

; Message variables for priting:
KEY_IS BYTE "Key is: ", 0
ENC_IS BYTE "Encrypted text is: ", 0
DEC_IS BYTE "Decrypted text is: ", 0
; Max Length for the string can be 100
MAX_LEN = 100
; =======================================================

; Declaring Variables
reGoChoice BYTE ? ;; Choice for re-go (returning to the beginning of the menu)
uChoice    DWORD ? ; Menu option will be stored in this variable
pHolder    DWORD ? ;; A simple placeholder that will hold a char
key		   BYTE MAX_LEN + 1 DUP(?) ; Key that will be used for encryption and decryption
cp_key     BYTE MAX_LEN + 1 DUP(?) ; A simple copier key
cipherText BYTE MAX_LEN + 1 DUP(?) ; Variable that will hold the text returned from Decrypt proc
plainText  BYTE MAX_LEN + 1 DUP(?) ; Variable that will hold the text returned from Encrypt proc

; Variables that will hold the length of each string
len_key    DWORD ?
len_cp_key DWORD ? ;; Copied key length
len_cipher DWORD ?
len_plain  DWORD ?
curr_len   DWORD ?

;; File handling related variables:
fileHandle HANDLE ?
bytesRead  DWORD ?
fileName   BYTE MAX_LEN + 1 DUP(?) ; File name that will be read.
fileData   BYTE MAX_LEN + 1 DUP(?) ; Data that is read from file.

;; output file names:
out_encrypt BYTE "encrypted.txt", 0
out_decrypt BYTE "decrypted.txt", 0
; =======================================================
