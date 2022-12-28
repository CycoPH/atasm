; DOS, FMS, and DUP memory and vectors
; For atasm
; Ken Jennings
;=================================================
; Page 7+ -- DOS FMS, DUP.SYS
; $0700 = Start of free memory when DOS is not loaded.
; Atari DOS2 specifications:
; $0700 to $077C is 125 bytes of Boot Sector and DOS config
; $077D to $1501 is DOS/FMS
; $1540 to $3306 is DUP.SYS and end varies by number of drive buffers.
; $1A7C to $1D7B is Drive and Sector buffers.  Varies by amount allocated. 
; $1D7C to $3306 (max) non-resident DUP.SYS utilities.
;
;=================================================
; Boot Sector in Memory
;
BFLAG =   $0700 ; Boot Flag (0) 
BRCNT =   $0701 ; Boot Record Count is number of consecutive sectors to read.
BLDADR =  $0702 ; Two byte sector load address (should be $0700)
BIWTARR = $0704 ; Two byte initialization address
JXBCONT = $0706 ; Value $4C, 6502 JMP.  To jump to address that follows:
XBCONT =  $0707 ; Two byte Boot Read Continuation address.
SABYTE =  $0709 ; Maximum number of concurrently open files. default 3, max 7.
DRVBYT =  $070A ; Drive bits, $1/$2/$4/$8 means drive 1/2/3/4 is connected to system.
;       ; $070B Unused buffer allocation direction.
SASA =    $070C ; Two Byte Buffer allocation start address. (points to $07CB)
DSFLG =   $070E ; DOS Flag. non-zero for second phase of boot (load DUP.SYS). 0 is no DUP. 1/2 is 128/256 byte sectors.
DFLINK =  $070F ; Two byte pointer to first sector of DOS.SYS.
BLDISP =  $0711 ; Displacement to sector link byte 125/$7D which points to next sector. 0 is EOF.
DFLADR =  $0712 ; Two byte address of the start of DOS.SYS
;       ; $0714 ; ... Continuation of Boot file. 
;
BSIO =    $076C ; Entry point to FMS disk sector I/O routine.
BSIOR =   $0772 ; ? Entry point to FMS disk handler ?
;       ; $0779 Write verify flag for disk I/O. $50 No verify. $57 Write + verify.
DFMSDH =  $07CB ; Entry point to 21-byte FMS device handler.
DINT =    $07E0 ; FMS Initialization routine. 
;
;=================================================
; Misc values related to DOS and file loading
;
; LOMEM_DOS =   $1CFC ; Default MEMLO (Mapping the Atari)
; LOMEM_DOS =   $1D7C ; Nonresident Part of DUP (Mapping the Atari)
LOMEM_DOS =     $2A80 ; First usable memory after DOS (Atari 800 Reference manual)
LOMEM_DOS_DUP = $3307 ; First usable memory after DOS and DUP 
;
;=================================================
; Atari RUN ADDRESS.  
;
; The binary load file has a structure specifying starting 
; address, and ending address, followed by the bytes to 
; load in that memory range.  This allows the executable
; file to be optimized and contain only the data needed to 
; load into different parts of memory rather than a flat
; file used on other systems which must include all the
; memeory, even the unused memory within the range of the 
; program's minimum/maximum addresses.
;
; DOS observes two special addresses when loading data.
; If the contents of the INIT address changes after loading
; a segment DOS calls that address immediately. If that routine
; returns to DOS cleanly then file loading continues.
;
DOS_INIT_ADDR = $02E2 ; Execute here immediately then resume loading.
;
; If the contents of the RUN address changes DOS waits until
; all segments from the file are loaded and then calls the RUN
; address target.
;
DOS_RUN_ADDR =  $02E0 ; Execute here when file loading completes.
