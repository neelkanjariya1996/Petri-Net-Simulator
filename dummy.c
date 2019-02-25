while (token present) {

	if (token present in inm) {
		decode();
	}

	if (token present in inb) {
		if (opcode == 5) {
			issue2();
		} else {
			issue1();
		}
	}

	if (token presnt in lib) {
		addr();
	}

	if (token presnt in adb) {
		load();
	}

	if (token presnet in aib) {
		alu();
	}

	if (token present in reb) {
		write();
	}

	print 
}

bool 
is_inm_empty
	if (inm_head > num_of_inst)
		return true;
	return false;	

is_inb_empty
	if (inb_head >= inb_tail)
		return true;
	return false;
is_lib_empty
is_adb_empty
is_aib_empty
is_reb_empty 

act_tok[6] = {0} //a[0] = inm, a[1] = inb, a[2] = aib a[3] =lib a[4] = adb a[5] = reb 
a[0] = num_of_inst 
decode () 
	a[0]--
	a[1]++ 
issue1 ()
	a[1]--
	a[2]++
issue2 ()
	a[1]--
	a[3]++
addr ()

token_present

head size--
tail size++
