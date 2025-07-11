class CC
{
	constructor()
	{
		this.c=10;
		this.c2=11;	
	}
	test(a, b)
	{
		log(this.c2);
		return a+b;  
	}
}
var my_cc=new CC
var fun = my_cc.test(3,4);

