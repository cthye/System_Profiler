
bin/measure_procedure:     file format elf64-x86-64


Disassembly of section .init:

0000000000400688 <_init>:
  400688:	48 83 ec 08          	sub    $0x8,%rsp
  40068c:	48 8b 05 65 19 20 00 	mov    0x201965(%rip),%rax        # 601ff8 <_DYNAMIC+0x1f0>
  400693:	48 85 c0             	test   %rax,%rax
  400696:	74 05                	je     40069d <_init+0x15>
  400698:	e8 d3 00 00 00       	callq  400770 <sqrt@plt+0x10>
  40069d:	48 83 c4 08          	add    $0x8,%rsp
  4006a1:	c3                   	retq   

Disassembly of section .plt:

00000000004006b0 <free@plt-0x10>:
  4006b0:	ff 35 52 19 20 00    	pushq  0x201952(%rip)        # 602008 <_GLOBAL_OFFSET_TABLE_+0x8>
  4006b6:	ff 25 54 19 20 00    	jmpq   *0x201954(%rip)        # 602010 <_GLOBAL_OFFSET_TABLE_+0x10>
  4006bc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006c0 <free@plt>:
  4006c0:	ff 25 52 19 20 00    	jmpq   *0x201952(%rip)        # 602018 <_GLOBAL_OFFSET_TABLE_+0x18>
  4006c6:	68 00 00 00 00       	pushq  $0x0
  4006cb:	e9 e0 ff ff ff       	jmpq   4006b0 <_init+0x28>

00000000004006d0 <puts@plt>:
  4006d0:	ff 25 4a 19 20 00    	jmpq   *0x20194a(%rip)        # 602020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4006d6:	68 01 00 00 00       	pushq  $0x1
  4006db:	e9 d0 ff ff ff       	jmpq   4006b0 <_init+0x28>

00000000004006e0 <fclose@plt>:
  4006e0:	ff 25 42 19 20 00    	jmpq   *0x201942(%rip)        # 602028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4006e6:	68 02 00 00 00       	pushq  $0x2
  4006eb:	e9 c0 ff ff ff       	jmpq   4006b0 <_init+0x28>

00000000004006f0 <__stack_chk_fail@plt>:
  4006f0:	ff 25 3a 19 20 00    	jmpq   *0x20193a(%rip)        # 602030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4006f6:	68 03 00 00 00       	pushq  $0x3
  4006fb:	e9 b0 ff ff ff       	jmpq   4006b0 <_init+0x28>

0000000000400700 <printf@plt>:
  400700:	ff 25 32 19 20 00    	jmpq   *0x201932(%rip)        # 602038 <_GLOBAL_OFFSET_TABLE_+0x38>
  400706:	68 04 00 00 00       	pushq  $0x4
  40070b:	e9 a0 ff ff ff       	jmpq   4006b0 <_init+0x28>

0000000000400710 <__libc_start_main@plt>:
  400710:	ff 25 2a 19 20 00    	jmpq   *0x20192a(%rip)        # 602040 <_GLOBAL_OFFSET_TABLE_+0x40>
  400716:	68 05 00 00 00       	pushq  $0x5
  40071b:	e9 90 ff ff ff       	jmpq   4006b0 <_init+0x28>

0000000000400720 <fprintf@plt>:
  400720:	ff 25 22 19 20 00    	jmpq   *0x201922(%rip)        # 602048 <_GLOBAL_OFFSET_TABLE_+0x48>
  400726:	68 06 00 00 00       	pushq  $0x6
  40072b:	e9 80 ff ff ff       	jmpq   4006b0 <_init+0x28>

0000000000400730 <malloc@plt>:
  400730:	ff 25 1a 19 20 00    	jmpq   *0x20191a(%rip)        # 602050 <_GLOBAL_OFFSET_TABLE_+0x50>
  400736:	68 07 00 00 00       	pushq  $0x7
  40073b:	e9 70 ff ff ff       	jmpq   4006b0 <_init+0x28>

0000000000400740 <fopen@plt>:
  400740:	ff 25 12 19 20 00    	jmpq   *0x201912(%rip)        # 602058 <_GLOBAL_OFFSET_TABLE_+0x58>
  400746:	68 08 00 00 00       	pushq  $0x8
  40074b:	e9 60 ff ff ff       	jmpq   4006b0 <_init+0x28>

0000000000400750 <fwrite@plt>:
  400750:	ff 25 0a 19 20 00    	jmpq   *0x20190a(%rip)        # 602060 <_GLOBAL_OFFSET_TABLE_+0x60>
  400756:	68 09 00 00 00       	pushq  $0x9
  40075b:	e9 50 ff ff ff       	jmpq   4006b0 <_init+0x28>

0000000000400760 <sqrt@plt>:
  400760:	ff 25 02 19 20 00    	jmpq   *0x201902(%rip)        # 602068 <_GLOBAL_OFFSET_TABLE_+0x68>
  400766:	68 0a 00 00 00       	pushq  $0xa
  40076b:	e9 40 ff ff ff       	jmpq   4006b0 <_init+0x28>

Disassembly of section .plt.got:

0000000000400770 <.plt.got>:
  400770:	ff 25 82 18 20 00    	jmpq   *0x201882(%rip)        # 601ff8 <_DYNAMIC+0x1f0>
  400776:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400780 <_start>:
  400780:	31 ed                	xor    %ebp,%ebp
  400782:	49 89 d1             	mov    %rdx,%r9
  400785:	5e                   	pop    %rsi
  400786:	48 89 e2             	mov    %rsp,%rdx
  400789:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40078d:	50                   	push   %rax
  40078e:	54                   	push   %rsp
  40078f:	49 c7 c0 30 11 40 00 	mov    $0x401130,%r8
  400796:	48 c7 c1 c0 10 40 00 	mov    $0x4010c0,%rcx
  40079d:	48 c7 c7 d6 0d 40 00 	mov    $0x400dd6,%rdi
  4007a4:	e8 67 ff ff ff       	callq  400710 <__libc_start_main@plt>
  4007a9:	f4                   	hlt    
  4007aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004007b0 <deregister_tm_clones>:
  4007b0:	b8 80 20 60 00       	mov    $0x602080,%eax
  4007b5:	48 3d 80 20 60 00    	cmp    $0x602080,%rax
  4007bb:	74 13                	je     4007d0 <deregister_tm_clones+0x20>
  4007bd:	b8 00 00 00 00       	mov    $0x0,%eax
  4007c2:	48 85 c0             	test   %rax,%rax
  4007c5:	74 09                	je     4007d0 <deregister_tm_clones+0x20>
  4007c7:	bf 80 20 60 00       	mov    $0x602080,%edi
  4007cc:	ff e0                	jmpq   *%rax
  4007ce:	66 90                	xchg   %ax,%ax
  4007d0:	c3                   	retq   
  4007d1:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4007d6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4007dd:	00 00 00 

00000000004007e0 <register_tm_clones>:
  4007e0:	be 80 20 60 00       	mov    $0x602080,%esi
  4007e5:	48 81 ee 80 20 60 00 	sub    $0x602080,%rsi
  4007ec:	48 89 f0             	mov    %rsi,%rax
  4007ef:	48 c1 ee 3f          	shr    $0x3f,%rsi
  4007f3:	48 c1 f8 03          	sar    $0x3,%rax
  4007f7:	48 01 c6             	add    %rax,%rsi
  4007fa:	48 d1 fe             	sar    %rsi
  4007fd:	74 11                	je     400810 <register_tm_clones+0x30>
  4007ff:	b8 00 00 00 00       	mov    $0x0,%eax
  400804:	48 85 c0             	test   %rax,%rax
  400807:	74 07                	je     400810 <register_tm_clones+0x30>
  400809:	bf 80 20 60 00       	mov    $0x602080,%edi
  40080e:	ff e0                	jmpq   *%rax
  400810:	c3                   	retq   
  400811:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400816:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40081d:	00 00 00 

0000000000400820 <__do_global_dtors_aux>:
  400820:	80 3d 59 18 20 00 00 	cmpb   $0x0,0x201859(%rip)        # 602080 <__TMC_END__>
  400827:	75 17                	jne    400840 <__do_global_dtors_aux+0x20>
  400829:	55                   	push   %rbp
  40082a:	48 89 e5             	mov    %rsp,%rbp
  40082d:	e8 7e ff ff ff       	callq  4007b0 <deregister_tm_clones>
  400832:	c6 05 47 18 20 00 01 	movb   $0x1,0x201847(%rip)        # 602080 <__TMC_END__>
  400839:	5d                   	pop    %rbp
  40083a:	c3                   	retq   
  40083b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400840:	c3                   	retq   
  400841:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400846:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40084d:	00 00 00 

0000000000400850 <frame_dummy>:
  400850:	eb 8e                	jmp    4007e0 <register_tm_clones>

0000000000400852 <cal_variance>:
  400852:	55                   	push   %rbp
  400853:	48 89 e5             	mov    %rsp,%rbp
  400856:	48 83 ec 30          	sub    $0x30,%rsp
  40085a:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  40085e:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
  400862:	48 89 55 d8          	mov    %rdx,-0x28(%rbp)
  400866:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  40086d:	00 
  40086e:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  400875:	eb 45                	jmp    4008bc <cal_variance+0x6a>
  400877:	8b 45 f4             	mov    -0xc(%rbp),%eax
  40087a:	48 98                	cltq   
  40087c:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400883:	00 
  400884:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  400888:	48 01 d0             	add    %rdx,%rax
  40088b:	48 8b 00             	mov    (%rax),%rax
  40088e:	48 2b 45 e0          	sub    -0x20(%rbp),%rax
  400892:	48 89 c2             	mov    %rax,%rdx
  400895:	8b 45 f4             	mov    -0xc(%rbp),%eax
  400898:	48 98                	cltq   
  40089a:	48 8d 0c c5 00 00 00 	lea    0x0(,%rax,8),%rcx
  4008a1:	00 
  4008a2:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  4008a6:	48 01 c8             	add    %rcx,%rax
  4008a9:	48 8b 00             	mov    (%rax),%rax
  4008ac:	48 2b 45 e0          	sub    -0x20(%rbp),%rax
  4008b0:	48 0f af c2          	imul   %rdx,%rax
  4008b4:	48 01 45 f8          	add    %rax,-0x8(%rbp)
  4008b8:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
  4008bc:	8b 45 f4             	mov    -0xc(%rbp),%eax
  4008bf:	48 98                	cltq   
  4008c1:	48 39 45 d8          	cmp    %rax,-0x28(%rbp)
  4008c5:	77 b0                	ja     400877 <cal_variance+0x25>
  4008c7:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4008cb:	ba 00 00 00 00       	mov    $0x0,%edx
  4008d0:	48 f7 75 d8          	divq   -0x28(%rbp)
  4008d4:	48 85 c0             	test   %rax,%rax
  4008d7:	78 07                	js     4008e0 <cal_variance+0x8e>
  4008d9:	f2 48 0f 2a c0       	cvtsi2sd %rax,%xmm0
  4008de:	eb 15                	jmp    4008f5 <cal_variance+0xa3>
  4008e0:	48 89 c2             	mov    %rax,%rdx
  4008e3:	48 d1 ea             	shr    %rdx
  4008e6:	83 e0 01             	and    $0x1,%eax
  4008e9:	48 09 c2             	or     %rax,%rdx
  4008ec:	f2 48 0f 2a c2       	cvtsi2sd %rdx,%xmm0
  4008f1:	f2 0f 58 c0          	addsd  %xmm0,%xmm0
  4008f5:	e8 66 fe ff ff       	callq  400760 <sqrt@plt>
  4008fa:	66 0f 2f 05 1e 0a 00 	comisd 0xa1e(%rip),%xmm0        # 401320 <BOUND_OF_LOOP+0xa0>
  400901:	00 
  400902:	73 07                	jae    40090b <cal_variance+0xb9>
  400904:	f2 48 0f 2c c0       	cvttsd2si %xmm0,%rax
  400909:	eb 1e                	jmp    400929 <cal_variance+0xd7>
  40090b:	f2 0f 10 0d 0d 0a 00 	movsd  0xa0d(%rip),%xmm1        # 401320 <BOUND_OF_LOOP+0xa0>
  400912:	00 
  400913:	f2 0f 5c c1          	subsd  %xmm1,%xmm0
  400917:	f2 48 0f 2c c0       	cvttsd2si %xmm0,%rax
  40091c:	48 ba 00 00 00 00 00 	movabs $0x8000000000000000,%rdx
  400923:	00 00 80 
  400926:	48 31 d0             	xor    %rdx,%rax
  400929:	c9                   	leaveq 
  40092a:	c3                   	retq   

000000000040092b <do_calculation>:
  40092b:	55                   	push   %rbp
  40092c:	48 89 e5             	mov    %rsp,%rbp
  40092f:	53                   	push   %rbx
  400930:	48 81 ec 88 00 00 00 	sub    $0x88,%rsp
  400937:	48 89 7d 98          	mov    %rdi,-0x68(%rbp)
  40093b:	89 75 94             	mov    %esi,-0x6c(%rbp)
  40093e:	89 55 90             	mov    %edx,-0x70(%rbp)
  400941:	48 89 4d 88          	mov    %rcx,-0x78(%rbp)
  400945:	4c 89 45 80          	mov    %r8,-0x80(%rbp)
  400949:	4c 89 8d 78 ff ff ff 	mov    %r9,-0x88(%rbp)
  400950:	48 b8 ff ff ff ff ff 	movabs $0x7fffffffffffffff,%rax
  400957:	ff ff 7f 
  40095a:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  40095e:	48 c7 45 b0 00 00 00 	movq   $0x0,-0x50(%rbp)
  400965:	00 
  400966:	48 c7 45 b8 00 00 00 	movq   $0x0,-0x48(%rbp)
  40096d:	00 
  40096e:	48 c7 45 c0 00 00 00 	movq   $0x0,-0x40(%rbp)
  400975:	00 
  400976:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  40097a:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  400981:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  400985:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  40098c:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  400993:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  40099a:	48 8b 45 10          	mov    0x10(%rbp),%rax
  40099e:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  4009a5:	8b 45 94             	mov    -0x6c(%rbp),%eax
  4009a8:	48 98                	cltq   
  4009aa:	48 c1 e0 03          	shl    $0x3,%rax
  4009ae:	48 89 c7             	mov    %rax,%rdi
  4009b1:	e8 7a fd ff ff       	callq  400730 <malloc@plt>
  4009b6:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  4009ba:	8b 45 94             	mov    -0x6c(%rbp),%eax
  4009bd:	48 98                	cltq   
  4009bf:	48 c1 e0 03          	shl    $0x3,%rax
  4009c3:	48 89 c7             	mov    %rax,%rdi
  4009c6:	e8 65 fd ff ff       	callq  400730 <malloc@plt>
  4009cb:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  4009cf:	48 8b 45 18          	mov    0x18(%rbp),%rax
  4009d3:	be 48 11 40 00       	mov    $0x401148,%esi
  4009d8:	48 89 c7             	mov    %rax,%rdi
  4009db:	e8 60 fd ff ff       	callq  400740 <fopen@plt>
  4009e0:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  4009e4:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  4009e9:	75 14                	jne    4009ff <do_calculation+0xd4>
  4009eb:	bf 4a 11 40 00       	mov    $0x40114a,%edi
  4009f0:	b8 00 00 00 00       	mov    $0x0,%eax
  4009f5:	e8 06 fd ff ff       	callq  400700 <printf@plt>
  4009fa:	e9 29 03 00 00       	jmpq   400d28 <do_calculation+0x3fd>
  4009ff:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400a03:	48 89 c1             	mov    %rax,%rcx
  400a06:	ba 46 00 00 00       	mov    $0x46,%edx
  400a0b:	be 01 00 00 00       	mov    $0x1,%esi
  400a10:	bf 60 11 40 00       	mov    $0x401160,%edi
  400a15:	e8 36 fd ff ff       	callq  400750 <fwrite@plt>
  400a1a:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
  400a21:	e9 de 01 00 00       	jmpq   400c04 <do_calculation+0x2d9>
  400a26:	48 c7 45 c8 00 00 00 	movq   $0x0,-0x38(%rbp)
  400a2d:	00 
  400a2e:	c7 45 a4 00 00 00 00 	movl   $0x0,-0x5c(%rbp)
  400a35:	e9 dd 00 00 00       	jmpq   400b17 <do_calculation+0x1ec>
  400a3a:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400a3d:	48 98                	cltq   
  400a3f:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400a46:	00 
  400a47:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  400a4b:	48 01 d0             	add    %rdx,%rax
  400a4e:	48 8b 00             	mov    (%rax),%rax
  400a51:	8b 55 a4             	mov    -0x5c(%rbp),%edx
  400a54:	48 63 d2             	movslq %edx,%rdx
  400a57:	48 c1 e2 03          	shl    $0x3,%rdx
  400a5b:	48 01 d0             	add    %rdx,%rax
  400a5e:	48 8b 30             	mov    (%rax),%rsi
  400a61:	8b 4d a4             	mov    -0x5c(%rbp),%ecx
  400a64:	8b 55 a0             	mov    -0x60(%rbp),%edx
  400a67:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400a6b:	49 89 f0             	mov    %rsi,%r8
  400a6e:	be a7 11 40 00       	mov    $0x4011a7,%esi
  400a73:	48 89 c7             	mov    %rax,%rdi
  400a76:	b8 00 00 00 00       	mov    $0x0,%eax
  400a7b:	e8 a0 fc ff ff       	callq  400720 <fprintf@plt>
  400a80:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400a83:	48 98                	cltq   
  400a85:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400a8c:	00 
  400a8d:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  400a91:	48 01 d0             	add    %rdx,%rax
  400a94:	48 8b 00             	mov    (%rax),%rax
  400a97:	8b 55 a4             	mov    -0x5c(%rbp),%edx
  400a9a:	48 63 d2             	movslq %edx,%rdx
  400a9d:	48 c1 e2 03          	shl    $0x3,%rdx
  400aa1:	48 01 d0             	add    %rdx,%rax
  400aa4:	48 8b 00             	mov    (%rax),%rax
  400aa7:	48 39 45 a8          	cmp    %rax,-0x58(%rbp)
  400aab:	48 0f 46 45 a8       	cmovbe -0x58(%rbp),%rax
  400ab0:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  400ab4:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400ab7:	48 98                	cltq   
  400ab9:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400ac0:	00 
  400ac1:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  400ac5:	48 01 d0             	add    %rdx,%rax
  400ac8:	48 8b 00             	mov    (%rax),%rax
  400acb:	8b 55 a4             	mov    -0x5c(%rbp),%edx
  400ace:	48 63 d2             	movslq %edx,%rdx
  400ad1:	48 c1 e2 03          	shl    $0x3,%rdx
  400ad5:	48 01 d0             	add    %rdx,%rax
  400ad8:	48 8b 00             	mov    (%rax),%rax
  400adb:	48 39 45 b0          	cmp    %rax,-0x50(%rbp)
  400adf:	48 0f 43 45 b0       	cmovae -0x50(%rbp),%rax
  400ae4:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  400ae8:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400aeb:	48 98                	cltq   
  400aed:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400af4:	00 
  400af5:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  400af9:	48 01 d0             	add    %rdx,%rax
  400afc:	48 8b 00             	mov    (%rax),%rax
  400aff:	8b 55 a4             	mov    -0x5c(%rbp),%edx
  400b02:	48 63 d2             	movslq %edx,%rdx
  400b05:	48 c1 e2 03          	shl    $0x3,%rdx
  400b09:	48 01 d0             	add    %rdx,%rax
  400b0c:	48 8b 00             	mov    (%rax),%rax
  400b0f:	48 01 45 c8          	add    %rax,-0x38(%rbp)
  400b13:	83 45 a4 01          	addl   $0x1,-0x5c(%rbp)
  400b17:	8b 45 a4             	mov    -0x5c(%rbp),%eax
  400b1a:	3b 45 90             	cmp    -0x70(%rbp),%eax
  400b1d:	0f 8c 17 ff ff ff    	jl     400a3a <do_calculation+0x10f>
  400b23:	8b 45 90             	mov    -0x70(%rbp),%eax
  400b26:	48 63 d8             	movslq %eax,%rbx
  400b29:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400b2c:	48 98                	cltq   
  400b2e:	48 8d 0c c5 00 00 00 	lea    0x0(,%rax,8),%rcx
  400b35:	00 
  400b36:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400b3a:	48 01 c1             	add    %rax,%rcx
  400b3d:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400b41:	ba 00 00 00 00       	mov    $0x0,%edx
  400b46:	48 f7 f3             	div    %rbx
  400b49:	48 89 01             	mov    %rax,(%rcx)
  400b4c:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400b4f:	48 98                	cltq   
  400b51:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400b58:	00 
  400b59:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400b5d:	48 01 d0             	add    %rdx,%rax
  400b60:	48 8b 00             	mov    (%rax),%rax
  400b63:	48 01 45 b8          	add    %rax,-0x48(%rbp)
  400b67:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  400b6b:	48 2b 45 a8          	sub    -0x58(%rbp),%rax
  400b6f:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  400b73:	48 8b 45 10          	mov    0x10(%rbp),%rax
  400b77:	48 8b 00             	mov    (%rax),%rax
  400b7a:	48 39 45 e8          	cmp    %rax,-0x18(%rbp)
  400b7e:	48 0f 43 45 e8       	cmovae -0x18(%rbp),%rax
  400b83:	48 89 c2             	mov    %rax,%rdx
  400b86:	48 8b 45 10          	mov    0x10(%rbp),%rax
  400b8a:	48 89 10             	mov    %rdx,(%rax)
  400b8d:	8b 45 94             	mov    -0x6c(%rbp),%eax
  400b90:	48 63 d0             	movslq %eax,%rdx
  400b93:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400b96:	48 98                	cltq   
  400b98:	48 8d 0c c5 00 00 00 	lea    0x0(,%rax,8),%rcx
  400b9f:	00 
  400ba0:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400ba4:	48 01 c8             	add    %rcx,%rax
  400ba7:	48 8b 08             	mov    (%rax),%rcx
  400baa:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400bad:	48 98                	cltq   
  400baf:	48 8d 34 c5 00 00 00 	lea    0x0(,%rax,8),%rsi
  400bb6:	00 
  400bb7:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  400bbb:	48 01 f0             	add    %rsi,%rax
  400bbe:	48 8b 00             	mov    (%rax),%rax
  400bc1:	8b 75 a0             	mov    -0x60(%rbp),%esi
  400bc4:	48 63 f6             	movslq %esi,%rsi
  400bc7:	48 8d 3c f5 00 00 00 	lea    0x0(,%rsi,8),%rdi
  400bce:	00 
  400bcf:	48 8b 75 d8          	mov    -0x28(%rbp),%rsi
  400bd3:	48 8d 1c 37          	lea    (%rdi,%rsi,1),%rbx
  400bd7:	48 89 ce             	mov    %rcx,%rsi
  400bda:	48 89 c7             	mov    %rax,%rdi
  400bdd:	e8 70 fc ff ff       	callq  400852 <cal_variance>
  400be2:	48 89 03             	mov    %rax,(%rbx)
  400be5:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400be8:	48 98                	cltq   
  400bea:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400bf1:	00 
  400bf2:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  400bf6:	48 01 d0             	add    %rdx,%rax
  400bf9:	48 8b 00             	mov    (%rax),%rax
  400bfc:	48 01 45 c0          	add    %rax,-0x40(%rbp)
  400c00:	83 45 a0 01          	addl   $0x1,-0x60(%rbp)
  400c04:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400c07:	3b 45 94             	cmp    -0x6c(%rbp),%eax
  400c0a:	0f 8c 16 fe ff ff    	jl     400a26 <do_calculation+0xfb>
  400c10:	8b 45 94             	mov    -0x6c(%rbp),%eax
  400c13:	48 63 d8             	movslq %eax,%rbx
  400c16:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  400c1a:	ba 00 00 00 00       	mov    $0x0,%edx
  400c1f:	48 f7 f3             	div    %rbx
  400c22:	48 89 c2             	mov    %rax,%rdx
  400c25:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  400c29:	48 89 10             	mov    %rdx,(%rax)
  400c2c:	8b 45 94             	mov    -0x6c(%rbp),%eax
  400c2f:	48 63 d8             	movslq %eax,%rbx
  400c32:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  400c36:	ba 00 00 00 00       	mov    $0x0,%edx
  400c3b:	48 f7 f3             	div    %rbx
  400c3e:	48 89 c2             	mov    %rax,%rdx
  400c41:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  400c45:	48 89 10             	mov    %rdx,(%rax)
  400c48:	8b 45 94             	mov    -0x6c(%rbp),%eax
  400c4b:	48 63 d0             	movslq %eax,%rdx
  400c4e:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  400c52:	48 8b 08             	mov    (%rax),%rcx
  400c55:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400c59:	48 89 ce             	mov    %rcx,%rsi
  400c5c:	48 89 c7             	mov    %rax,%rdi
  400c5f:	e8 ee fb ff ff       	callq  400852 <cal_variance>
  400c64:	48 8b 95 78 ff ff ff 	mov    -0x88(%rbp),%rdx
  400c6b:	48 89 02             	mov    %rax,(%rdx)
  400c6e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400c72:	48 89 c1             	mov    %rax,%rcx
  400c75:	ba 45 00 00 00       	mov    $0x45,%edx
  400c7a:	be 01 00 00 00       	mov    $0x1,%esi
  400c7f:	bf c8 11 40 00       	mov    $0x4011c8,%edi
  400c84:	e8 c7 fa ff ff       	callq  400750 <fwrite@plt>
  400c89:	8b 4d 90             	mov    -0x70(%rbp),%ecx
  400c8c:	8b 55 94             	mov    -0x6c(%rbp),%edx
  400c8f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400c93:	be 10 12 40 00       	mov    $0x401210,%esi
  400c98:	48 89 c7             	mov    %rax,%rdi
  400c9b:	b8 00 00 00 00       	mov    $0x0,%eax
  400ca0:	e8 7b fa ff ff       	callq  400720 <fprintf@plt>
  400ca5:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  400ca9:	48 8b 10             	mov    (%rax),%rdx
  400cac:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400cb0:	be 37 12 40 00       	mov    $0x401237,%esi
  400cb5:	48 89 c7             	mov    %rax,%rdi
  400cb8:	b8 00 00 00 00       	mov    $0x0,%eax
  400cbd:	e8 5e fa ff ff       	callq  400720 <fprintf@plt>
  400cc2:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  400cc6:	48 8b 10             	mov    (%rax),%rdx
  400cc9:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400ccd:	be 41 12 40 00       	mov    $0x401241,%esi
  400cd2:	48 89 c7             	mov    %rax,%rdi
  400cd5:	b8 00 00 00 00       	mov    $0x0,%eax
  400cda:	e8 41 fa ff ff       	callq  400720 <fprintf@plt>
  400cdf:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  400ce6:	48 8b 10             	mov    (%rax),%rdx
  400ce9:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400ced:	be 4f 12 40 00       	mov    $0x40124f,%esi
  400cf2:	48 89 c7             	mov    %rax,%rdi
  400cf5:	b8 00 00 00 00       	mov    $0x0,%eax
  400cfa:	e8 21 fa ff ff       	callq  400720 <fprintf@plt>
  400cff:	48 8b 45 10          	mov    0x10(%rbp),%rax
  400d03:	48 8b 10             	mov    (%rax),%rdx
  400d06:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d0a:	be 65 12 40 00       	mov    $0x401265,%esi
  400d0f:	48 89 c7             	mov    %rax,%rdi
  400d12:	b8 00 00 00 00       	mov    $0x0,%eax
  400d17:	e8 04 fa ff ff       	callq  400720 <fprintf@plt>
  400d1c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d20:	48 89 c7             	mov    %rax,%rdi
  400d23:	e8 b8 f9 ff ff       	callq  4006e0 <fclose@plt>
  400d28:	48 81 c4 88 00 00 00 	add    $0x88,%rsp
  400d2f:	5b                   	pop    %rbx
  400d30:	5d                   	pop    %rbp
  400d31:	c3                   	retq   

0000000000400d32 <procedure_0>:
  400d32:	55                   	push   %rbp
  400d33:	48 89 e5             	mov    %rsp,%rbp
  400d36:	90                   	nop
  400d37:	5d                   	pop    %rbp
  400d38:	c3                   	retq   

0000000000400d39 <procedure_1>:
  400d39:	55                   	push   %rbp
  400d3a:	48 89 e5             	mov    %rsp,%rbp
  400d3d:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400d41:	90                   	nop
  400d42:	5d                   	pop    %rbp
  400d43:	c3                   	retq   

0000000000400d44 <procedure_2>:
  400d44:	55                   	push   %rbp
  400d45:	48 89 e5             	mov    %rsp,%rbp
  400d48:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400d4c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  400d50:	90                   	nop
  400d51:	5d                   	pop    %rbp
  400d52:	c3                   	retq   

0000000000400d53 <procedure_3>:
  400d53:	55                   	push   %rbp
  400d54:	48 89 e5             	mov    %rsp,%rbp
  400d57:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400d5b:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  400d5f:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  400d63:	90                   	nop
  400d64:	5d                   	pop    %rbp
  400d65:	c3                   	retq   

0000000000400d66 <procedure_4>:
  400d66:	55                   	push   %rbp
  400d67:	48 89 e5             	mov    %rsp,%rbp
  400d6a:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400d6e:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  400d72:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  400d76:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  400d7a:	90                   	nop
  400d7b:	5d                   	pop    %rbp
  400d7c:	c3                   	retq   

0000000000400d7d <procedure_5>:
  400d7d:	55                   	push   %rbp
  400d7e:	48 89 e5             	mov    %rsp,%rbp
  400d81:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400d85:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  400d89:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  400d8d:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  400d91:	4c 89 45 d8          	mov    %r8,-0x28(%rbp)
  400d95:	90                   	nop
  400d96:	5d                   	pop    %rbp
  400d97:	c3                   	retq   

0000000000400d98 <procedure_6>:
  400d98:	55                   	push   %rbp
  400d99:	48 89 e5             	mov    %rsp,%rbp
  400d9c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400da0:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  400da4:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  400da8:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  400dac:	4c 89 45 d8          	mov    %r8,-0x28(%rbp)
  400db0:	4c 89 4d d0          	mov    %r9,-0x30(%rbp)
  400db4:	90                   	nop
  400db5:	5d                   	pop    %rbp
  400db6:	c3                   	retq   

0000000000400db7 <procedure_7>:
  400db7:	55                   	push   %rbp
  400db8:	48 89 e5             	mov    %rsp,%rbp
  400dbb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400dbf:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  400dc3:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  400dc7:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  400dcb:	4c 89 45 d8          	mov    %r8,-0x28(%rbp)
  400dcf:	4c 89 4d d0          	mov    %r9,-0x30(%rbp)
  400dd3:	90                   	nop
  400dd4:	5d                   	pop    %rbp
  400dd5:	c3                   	retq   

0000000000400dd6 <main>:
  400dd6:	55                   	push   %rbp
  400dd7:	48 89 e5             	mov    %rsp,%rbp
  400dda:	53                   	push   %rbx
  400ddb:	48 83 ec 78          	sub    $0x78,%rsp
  400ddf:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400de6:	00 00 
  400de8:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  400dec:	31 c0                	xor    %eax,%eax
  400dee:	b8 64 00 00 00       	mov    $0x64,%eax
  400df3:	83 c0 01             	add    $0x1,%eax
  400df6:	48 98                	cltq   
  400df8:	48 c1 e0 03          	shl    $0x3,%rax
  400dfc:	48 89 c7             	mov    %rax,%rdi
  400dff:	e8 2c f9 ff ff       	callq  400730 <malloc@plt>
  400e04:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  400e08:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
  400e0d:	75 14                	jne    400e23 <main+0x4d>
  400e0f:	bf 88 12 40 00       	mov    $0x401288,%edi
  400e14:	e8 b7 f8 ff ff       	callq  4006d0 <puts@plt>
  400e19:	b8 00 00 00 00       	mov    $0x0,%eax
  400e1e:	e9 81 02 00 00       	jmpq   4010a4 <main+0x2ce>
  400e23:	c7 45 88 00 00 00 00 	movl   $0x0,-0x78(%rbp)
  400e2a:	e9 9e 00 00 00       	jmpq   400ecd <main+0xf7>
  400e2f:	b8 64 00 00 00       	mov    $0x64,%eax
  400e34:	48 98                	cltq   
  400e36:	48 c1 e0 03          	shl    $0x3,%rax
  400e3a:	8b 55 88             	mov    -0x78(%rbp),%edx
  400e3d:	48 63 d2             	movslq %edx,%rdx
  400e40:	48 8d 0c d5 00 00 00 	lea    0x0(,%rdx,8),%rcx
  400e47:	00 
  400e48:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  400e4c:	48 8d 1c 11          	lea    (%rcx,%rdx,1),%rbx
  400e50:	48 89 c7             	mov    %rax,%rdi
  400e53:	e8 d8 f8 ff ff       	callq  400730 <malloc@plt>
  400e58:	48 89 03             	mov    %rax,(%rbx)
  400e5b:	8b 45 88             	mov    -0x78(%rbp),%eax
  400e5e:	48 98                	cltq   
  400e60:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400e67:	00 
  400e68:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400e6c:	48 01 d0             	add    %rdx,%rax
  400e6f:	48 8b 00             	mov    (%rax),%rax
  400e72:	48 85 c0             	test   %rax,%rax
  400e75:	75 52                	jne    400ec9 <main+0xf3>
  400e77:	8b 45 88             	mov    -0x78(%rbp),%eax
  400e7a:	89 c6                	mov    %eax,%esi
  400e7c:	bf b0 12 40 00       	mov    $0x4012b0,%edi
  400e81:	b8 00 00 00 00       	mov    $0x0,%eax
  400e86:	e8 75 f8 ff ff       	callq  400700 <printf@plt>
  400e8b:	c7 45 8c 00 00 00 00 	movl   $0x0,-0x74(%rbp)
  400e92:	eb 23                	jmp    400eb7 <main+0xe1>
  400e94:	8b 45 8c             	mov    -0x74(%rbp),%eax
  400e97:	48 98                	cltq   
  400e99:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400ea0:	00 
  400ea1:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400ea5:	48 01 d0             	add    %rdx,%rax
  400ea8:	48 8b 00             	mov    (%rax),%rax
  400eab:	48 89 c7             	mov    %rax,%rdi
  400eae:	e8 0d f8 ff ff       	callq  4006c0 <free@plt>
  400eb3:	83 45 8c 01          	addl   $0x1,-0x74(%rbp)
  400eb7:	8b 45 8c             	mov    -0x74(%rbp),%eax
  400eba:	3b 45 88             	cmp    -0x78(%rbp),%eax
  400ebd:	7c d5                	jl     400e94 <main+0xbe>
  400ebf:	b8 00 00 00 00       	mov    $0x0,%eax
  400ec4:	e9 db 01 00 00       	jmpq   4010a4 <main+0x2ce>
  400ec9:	83 45 88 01          	addl   $0x1,-0x78(%rbp)
  400ecd:	b8 64 00 00 00       	mov    $0x64,%eax
  400ed2:	39 45 88             	cmp    %eax,-0x78(%rbp)
  400ed5:	0f 8e 54 ff ff ff    	jle    400e2f <main+0x59>
  400edb:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
  400ee2:	e9 c5 00 00 00       	jmpq   400fac <main+0x1d6>
  400ee7:	c7 45 94 00 00 00 00 	movl   $0x0,-0x6c(%rbp)
  400eee:	e9 a7 00 00 00       	jmpq   400f9a <main+0x1c4>
  400ef3:	0f a2                	cpuid  
  400ef5:	0f 31                	rdtsc  
  400ef7:	89 d7                	mov    %edx,%edi
  400ef9:	89 c6                	mov    %eax,%esi
  400efb:	89 7d 98             	mov    %edi,-0x68(%rbp)
  400efe:	89 75 9c             	mov    %esi,-0x64(%rbp)
  400f01:	48 83 ec 08          	sub    $0x8,%rsp
  400f05:	6a 00                	pushq  $0x0
  400f07:	41 b9 00 00 00 00    	mov    $0x0,%r9d
  400f0d:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  400f13:	b9 00 00 00 00       	mov    $0x0,%ecx
  400f18:	ba 00 00 00 00       	mov    $0x0,%edx
  400f1d:	be 00 00 00 00       	mov    $0x0,%esi
  400f22:	bf 00 00 00 00       	mov    $0x0,%edi
  400f27:	e8 8b fe ff ff       	callq  400db7 <procedure_7>
  400f2c:	48 83 c4 10          	add    $0x10,%rsp
  400f30:	0f 01 f9             	rdtscp 
  400f33:	89 d7                	mov    %edx,%edi
  400f35:	89 c6                	mov    %eax,%esi
  400f37:	0f a2                	cpuid  
  400f39:	89 7d a0             	mov    %edi,-0x60(%rbp)
  400f3c:	89 75 a4             	mov    %esi,-0x5c(%rbp)
  400f3f:	8b 45 98             	mov    -0x68(%rbp),%eax
  400f42:	48 c1 e0 20          	shl    $0x20,%rax
  400f46:	48 89 c2             	mov    %rax,%rdx
  400f49:	8b 45 9c             	mov    -0x64(%rbp),%eax
  400f4c:	48 09 d0             	or     %rdx,%rax
  400f4f:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  400f53:	8b 45 a0             	mov    -0x60(%rbp),%eax
  400f56:	48 c1 e0 20          	shl    $0x20,%rax
  400f5a:	48 89 c2             	mov    %rax,%rdx
  400f5d:	8b 45 a4             	mov    -0x5c(%rbp),%eax
  400f60:	48 09 d0             	or     %rdx,%rax
  400f63:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  400f67:	8b 45 90             	mov    -0x70(%rbp),%eax
  400f6a:	48 98                	cltq   
  400f6c:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  400f73:	00 
  400f74:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400f78:	48 01 d0             	add    %rdx,%rax
  400f7b:	48 8b 00             	mov    (%rax),%rax
  400f7e:	8b 55 94             	mov    -0x6c(%rbp),%edx
  400f81:	48 63 d2             	movslq %edx,%rdx
  400f84:	48 c1 e2 03          	shl    $0x3,%rdx
  400f88:	48 01 c2             	add    %rax,%rdx
  400f8b:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400f8f:	48 2b 45 d8          	sub    -0x28(%rbp),%rax
  400f93:	48 89 02             	mov    %rax,(%rdx)
  400f96:	83 45 94 01          	addl   $0x1,-0x6c(%rbp)
  400f9a:	b8 64 00 00 00       	mov    $0x64,%eax
  400f9f:	39 45 94             	cmp    %eax,-0x6c(%rbp)
  400fa2:	0f 8c 4b ff ff ff    	jl     400ef3 <main+0x11d>
  400fa8:	83 45 90 01          	addl   $0x1,-0x70(%rbp)
  400fac:	b8 64 00 00 00       	mov    $0x64,%eax
  400fb1:	39 45 90             	cmp    %eax,-0x70(%rbp)
  400fb4:	0f 8e 2d ff ff ff    	jle    400ee7 <main+0x111>
  400fba:	48 c7 45 a8 00 00 00 	movq   $0x0,-0x58(%rbp)
  400fc1:	00 
  400fc2:	48 c7 45 b0 00 00 00 	movq   $0x0,-0x50(%rbp)
  400fc9:	00 
  400fca:	48 c7 45 b8 00 00 00 	movq   $0x0,-0x48(%rbp)
  400fd1:	00 
  400fd2:	48 c7 45 c0 00 00 00 	movq   $0x0,-0x40(%rbp)
  400fd9:	00 
  400fda:	48 c7 45 d0 db 12 40 	movq   $0x4012db,-0x30(%rbp)
  400fe1:	00 
  400fe2:	41 bb 64 00 00 00    	mov    $0x64,%r11d
  400fe8:	41 ba 64 00 00 00    	mov    $0x64,%r10d
  400fee:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400ff2:	48 8d 78 08          	lea    0x8(%rax),%rdi
  400ff6:	48 8d 75 b8          	lea    -0x48(%rbp),%rsi
  400ffa:	48 8d 4d b0          	lea    -0x50(%rbp),%rcx
  400ffe:	48 8d 45 a8          	lea    -0x58(%rbp),%rax
  401002:	ff 75 d0             	pushq  -0x30(%rbp)
  401005:	48 8d 55 c0          	lea    -0x40(%rbp),%rdx
  401009:	52                   	push   %rdx
  40100a:	49 89 f1             	mov    %rsi,%r9
  40100d:	49 89 c8             	mov    %rcx,%r8
  401010:	48 89 c1             	mov    %rax,%rcx
  401013:	44 89 da             	mov    %r11d,%edx
  401016:	44 89 d6             	mov    %r10d,%esi
  401019:	e8 0d f9 ff ff       	callq  40092b <do_calculation>
  40101e:	48 83 c4 10          	add    $0x10,%rsp
  401022:	bf f8 12 40 00       	mov    $0x4012f8,%edi
  401027:	e8 a4 f6 ff ff       	callq  4006d0 <puts@plt>
  40102c:	ba 64 00 00 00       	mov    $0x64,%edx
  401031:	b8 64 00 00 00       	mov    $0x64,%eax
  401036:	89 c6                	mov    %eax,%esi
  401038:	bf 10 12 40 00       	mov    $0x401210,%edi
  40103d:	b8 00 00 00 00       	mov    $0x0,%eax
  401042:	e8 b9 f6 ff ff       	callq  400700 <printf@plt>
  401047:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  40104b:	48 89 c6             	mov    %rax,%rsi
  40104e:	bf 37 12 40 00       	mov    $0x401237,%edi
  401053:	b8 00 00 00 00       	mov    $0x0,%eax
  401058:	e8 a3 f6 ff ff       	callq  400700 <printf@plt>
  40105d:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  401061:	48 89 c6             	mov    %rax,%rsi
  401064:	bf 41 12 40 00       	mov    $0x401241,%edi
  401069:	b8 00 00 00 00       	mov    $0x0,%eax
  40106e:	e8 8d f6 ff ff       	callq  400700 <printf@plt>
  401073:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  401077:	48 89 c6             	mov    %rax,%rsi
  40107a:	bf 4f 12 40 00       	mov    $0x40124f,%edi
  40107f:	b8 00 00 00 00       	mov    $0x0,%eax
  401084:	e8 77 f6 ff ff       	callq  400700 <printf@plt>
  401089:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  40108d:	48 89 c6             	mov    %rax,%rsi
  401090:	bf 65 12 40 00       	mov    $0x401265,%edi
  401095:	b8 00 00 00 00       	mov    $0x0,%eax
  40109a:	e8 61 f6 ff ff       	callq  400700 <printf@plt>
  40109f:	b8 00 00 00 00       	mov    $0x0,%eax
  4010a4:	48 8b 5d e8          	mov    -0x18(%rbp),%rbx
  4010a8:	64 48 33 1c 25 28 00 	xor    %fs:0x28,%rbx
  4010af:	00 00 
  4010b1:	74 05                	je     4010b8 <main+0x2e2>
  4010b3:	e8 38 f6 ff ff       	callq  4006f0 <__stack_chk_fail@plt>
  4010b8:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
  4010bc:	c9                   	leaveq 
  4010bd:	c3                   	retq   
  4010be:	66 90                	xchg   %ax,%ax

00000000004010c0 <__libc_csu_init>:
  4010c0:	41 57                	push   %r15
  4010c2:	41 56                	push   %r14
  4010c4:	41 89 ff             	mov    %edi,%r15d
  4010c7:	41 55                	push   %r13
  4010c9:	41 54                	push   %r12
  4010cb:	4c 8d 25 26 0d 20 00 	lea    0x200d26(%rip),%r12        # 601df8 <__frame_dummy_init_array_entry>
  4010d2:	55                   	push   %rbp
  4010d3:	48 8d 2d 26 0d 20 00 	lea    0x200d26(%rip),%rbp        # 601e00 <__init_array_end>
  4010da:	53                   	push   %rbx
  4010db:	49 89 f6             	mov    %rsi,%r14
  4010de:	49 89 d5             	mov    %rdx,%r13
  4010e1:	4c 29 e5             	sub    %r12,%rbp
  4010e4:	48 83 ec 08          	sub    $0x8,%rsp
  4010e8:	48 c1 fd 03          	sar    $0x3,%rbp
  4010ec:	e8 97 f5 ff ff       	callq  400688 <_init>
  4010f1:	48 85 ed             	test   %rbp,%rbp
  4010f4:	74 20                	je     401116 <__libc_csu_init+0x56>
  4010f6:	31 db                	xor    %ebx,%ebx
  4010f8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4010ff:	00 
  401100:	4c 89 ea             	mov    %r13,%rdx
  401103:	4c 89 f6             	mov    %r14,%rsi
  401106:	44 89 ff             	mov    %r15d,%edi
  401109:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40110d:	48 83 c3 01          	add    $0x1,%rbx
  401111:	48 39 eb             	cmp    %rbp,%rbx
  401114:	75 ea                	jne    401100 <__libc_csu_init+0x40>
  401116:	48 83 c4 08          	add    $0x8,%rsp
  40111a:	5b                   	pop    %rbx
  40111b:	5d                   	pop    %rbp
  40111c:	41 5c                	pop    %r12
  40111e:	41 5d                	pop    %r13
  401120:	41 5e                	pop    %r14
  401122:	41 5f                	pop    %r15
  401124:	c3                   	retq   
  401125:	90                   	nop
  401126:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40112d:	00 00 00 

0000000000401130 <__libc_csu_fini>:
  401130:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000401134 <_fini>:
  401134:	48 83 ec 08          	sub    $0x8,%rsp
  401138:	48 83 c4 08          	add    $0x8,%rsp
  40113c:	c3                   	retq   
