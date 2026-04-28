global MyStrlen

section .text

;-----------------------
;counting len of max-32-len string using SSE instructions
;1st arg - prt to char*
;-----------------------
MyStrlen:
    vmovups ymm0, [rcx]
    vpxor ymm1, ymm1, ymm1

    vpcmpeqb ymm0, ymm0, ymm1

    vpmovmskb eax, ymm0 

    tzcnt eax, eax
    ret
;-----------------------