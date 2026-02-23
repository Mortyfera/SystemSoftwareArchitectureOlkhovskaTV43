
pr2_13_opt:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	push   0x2f9a(%rip)        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 9c 2f 00 00    	jmp    *0x2f9c(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)
    1030:	f3 0f 1e fa          	endbr64
    1034:	68 00 00 00 00       	push   $0x0
    1039:	e9 e2 ff ff ff       	jmp    1020 <_init+0x20>
    103e:	66 90                	xchg   %ax,%ax

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64
    1044:	ff 25 ae 2f 00 00    	jmp    *0x2fae(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001050 <__printf_chk@plt>:
    1050:	f3 0f 1e fa          	endbr64
    1054:	ff 25 76 2f 00 00    	jmp    *0x2f76(%rip)        # 3fd0 <__printf_chk@GLIBC_2.3.4>
    105a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001060 <main>:
    1060:	f3 0f 1e fa          	endbr64
    1064:	50                   	push   %rax
    1065:	31 c0                	xor    %eax,%eax
    1067:	e8 ed 00 00 00       	call   1159 <function>
    106c:	31 c0                	xor    %eax,%eax
    106e:	5a                   	pop    %rdx
    106f:	c3                   	ret

0000000000001070 <_start>:
    1070:	f3 0f 1e fa          	endbr64
    1074:	31 ed                	xor    %ebp,%ebp
    1076:	49 89 d1             	mov    %rdx,%r9
    1079:	5e                   	pop    %rsi
    107a:	48 89 e2             	mov    %rsp,%rdx
    107d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1081:	50                   	push   %rax
    1082:	54                   	push   %rsp
    1083:	45 31 c0             	xor    %r8d,%r8d
    1086:	31 c9                	xor    %ecx,%ecx
    1088:	48 8d 3d d1 ff ff ff 	lea    -0x2f(%rip),%rdi        # 1060 <main>
    108f:	ff 15 43 2f 00 00    	call   *0x2f43(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1095:	f4                   	hlt
    1096:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    109d:	00 00 00 

00000000000010a0 <deregister_tm_clones>:
    10a0:	48 8d 3d 71 2f 00 00 	lea    0x2f71(%rip),%rdi        # 4018 <__TMC_END__>
    10a7:	48 8d 05 6a 2f 00 00 	lea    0x2f6a(%rip),%rax        # 4018 <__TMC_END__>
    10ae:	48 39 f8             	cmp    %rdi,%rax
    10b1:	74 15                	je     10c8 <deregister_tm_clones+0x28>
    10b3:	48 8b 05 26 2f 00 00 	mov    0x2f26(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10ba:	48 85 c0             	test   %rax,%rax
    10bd:	74 09                	je     10c8 <deregister_tm_clones+0x28>
    10bf:	ff e0                	jmp    *%rax
    10c1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10c8:	c3                   	ret
    10c9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010d0 <register_tm_clones>:
    10d0:	48 8d 3d 41 2f 00 00 	lea    0x2f41(%rip),%rdi        # 4018 <__TMC_END__>
    10d7:	48 8d 35 3a 2f 00 00 	lea    0x2f3a(%rip),%rsi        # 4018 <__TMC_END__>
    10de:	48 29 fe             	sub    %rdi,%rsi
    10e1:	48 89 f0             	mov    %rsi,%rax
    10e4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10e8:	48 c1 f8 03          	sar    $0x3,%rax
    10ec:	48 01 c6             	add    %rax,%rsi
    10ef:	48 d1 fe             	sar    $1,%rsi
    10f2:	74 14                	je     1108 <register_tm_clones+0x38>
    10f4:	48 8b 05 f5 2e 00 00 	mov    0x2ef5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10fb:	48 85 c0             	test   %rax,%rax
    10fe:	74 08                	je     1108 <register_tm_clones+0x38>
    1100:	ff e0                	jmp    *%rax
    1102:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1108:	c3                   	ret
    1109:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001110 <__do_global_dtors_aux>:
    1110:	f3 0f 1e fa          	endbr64
    1114:	80 3d 05 2f 00 00 00 	cmpb   $0x0,0x2f05(%rip)        # 4020 <completed.0>
    111b:	75 2b                	jne    1148 <__do_global_dtors_aux+0x38>
    111d:	55                   	push   %rbp
    111e:	48 83 3d d2 2e 00 00 	cmpq   $0x0,0x2ed2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1125:	00 
    1126:	48 89 e5             	mov    %rsp,%rbp
    1129:	74 0c                	je     1137 <__do_global_dtors_aux+0x27>
    112b:	48 8b 3d d6 2e 00 00 	mov    0x2ed6(%rip),%rdi        # 4008 <__dso_handle>
    1132:	e8 09 ff ff ff       	call   1040 <__cxa_finalize@plt>
    1137:	e8 64 ff ff ff       	call   10a0 <deregister_tm_clones>
    113c:	c6 05 dd 2e 00 00 01 	movb   $0x1,0x2edd(%rip)        # 4020 <completed.0>
    1143:	5d                   	pop    %rbp
    1144:	c3                   	ret
    1145:	0f 1f 00             	nopl   (%rax)
    1148:	c3                   	ret
    1149:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001150 <frame_dummy>:
    1150:	f3 0f 1e fa          	endbr64
    1154:	e9 77 ff ff ff       	jmp    10d0 <register_tm_clones>

0000000000001159 <function>:
    1159:	f3 0f 1e fa          	endbr64
    115d:	48 8d 05 dc 2e 00 00 	lea    0x2edc(%rip),%rax        # 4040 <uninitialized_array>
    1164:	8b 15 a6 2e 00 00    	mov    0x2ea6(%rip),%edx        # 4010 <initialized_variable>
    116a:	31 c9                	xor    %ecx,%ecx
    116c:	48 8d b0 a0 0f 00 00 	lea    0xfa0(%rax),%rsi
    1173:	89 08                	mov    %ecx,(%rax)
    1175:	48 83 c0 04          	add    $0x4,%rax
    1179:	01 d1                	add    %edx,%ecx
    117b:	48 39 f0             	cmp    %rsi,%rax
    117e:	75 f3                	jne    1173 <function+0x1a>
    1180:	69 d2 2c 9f 07 00    	imul   $0x79f2c,%edx,%edx
    1186:	48 8d 35 77 0e 00 00 	lea    0xe77(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    118d:	bf 02 00 00 00       	mov    $0x2,%edi
    1192:	31 c0                	xor    %eax,%eax
    1194:	e9 b7 fe ff ff       	jmp    1050 <__printf_chk@plt>

Disassembly of section .fini:

000000000000119c <_fini>:
    119c:	f3 0f 1e fa          	endbr64
    11a0:	48 83 ec 08          	sub    $0x8,%rsp
    11a4:	48 83 c4 08          	add    $0x8,%rsp
    11a8:	c3                   	ret
