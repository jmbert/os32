
.section .text

.global _get_pdir
_get_pdir:
    mov %cr3, %eax
    ret

.global _invlpg
_invlpg:
    invlpg (%eax)
    ret
