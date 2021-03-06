#include <iostream>
#include <iomanip>          //setw() setprecision()  setfill()
using namespace std;

//格式化输出
int main(int argc, char* argv[])
{
	//01-调整字段宽度     临时（只影响接下来的）   streamsize本VS中是long long
	/* streamsize width()       //返回当前宽度，默认是0
	 * streamsize width(streamsize i)  //设置宽度为i,并返回之前的宽度 
	 */
	long long w = cout.width(30);   //0
	w = cout.width();         //30
	w = cout.width();         //30
	cout << 123 << endl;
	w = cout.width();         //0

	cout << setw(12) << 1 << endl;    //常用


	//02-填充字符  默认填充是空格    永久
	/* CharT fill() const;        (1)同width
     * CharT fill( CharT ch );    (2)
	 */
	char ch = cout.fill();            
	cout.fill('*');
	cout << setw(10) << 123 << endl;
	cout << setw(10) << 123 << endl;

	cout << setfill('*');

	//03-设置浮点数的显示精度          永久
	/* streamsize precision()                      //返回当前精度，默认是6
	 * streamsize precision(streamsize new_preci)  //设置精度为new,并返回之前的精度 
	 */
	long long prec = cout.precision(12);
	cout << 12.5;
	cout << 25.3;
	prec = cout.precision();

	cout << setprecision(12);

	//04-打印末尾的0和小数点
	//ios_base::showpoint是一个枚举值，静态常量
	//static constexpr _Fmtflags showpoint = (_Fmtflags)_IOSshowpoint;
	cout.setf(ios_base::showpoint);
	cout << 2.0 << endl;         //不加cout.setf(ios_base::showpoint); 显示为2；加的话，显示为2.00000
	cout << 2 << endl;           //加或者不加都是2, 推论：整数还是显示整数
	cout << 20000.0 << endl;     //显示20000.0
	cout << 200000.0 << endl;    //显示200000.
	cout << 2000000.0 << endl;   //2.00000e+06
	cout << fixed << 2000000.0 << endl;   //2000000.000000  貌似如果整数位数超过prec的话，小数点个数表示prec个
	//05-再谈setf()        永久   ---置对应的标记为1
	/* fmtflags VS中是int
	 * fmtflags setf( fmtflags flags );  (1) 
	 * fmtflags setf( fmtflags flags, fmtflags mask );  (2)  //常用的mask只有3个basefield， adjustfield， floatfield
	 */
	// (1) --------------------------
	cout.setf(ios_base::boolalpha);   //显示true false,  not 0 or 1
	cout.setf(ios_base::showbase);    //显示基数前缀0, 0x
	cout.setf(ios_base::showpoint);   //显示末尾的小数点
	cout.setf(ios_base::uppercase);   //显示16进制大写，以及E
	cout.setf(ios_base::showpos);     //正数前面加上‘+’

	// (2) ---------------------------
	//进制
	cout.setf(ios_base::dec, ios_base::basefield);   //默认
	cout.setf(ios_base::oct, ios_base::basefield);
	cout.setf(ios_base::hex, ios_base::basefield);

	//浮点计数相关    没有专门指示浮点数默认显示模式的标记
	cout.setf(ios_base::fixed, ios_base::floatfield);      //定点计数法  
	cout.setf(ios_base::scientific, ios_base::floatfield); //科学
	cout.setf(0, ios_base::floatfield);    //默认

	//对齐调整
	cout.setf(ios_base::left, ios_base::adjustfield);
	cout.setf(ios_base::right, ios_base::adjustfield);      //默认
	cout.setf(ios_base::internal, ios_base::adjustfield);   //符号或者基数前缀左对齐，值右对齐
	
	//如何恢复设置
	//(1)
	ios_base::fmtflags old = cout.setf(ios_base::showbase);
	cout.setf(old);
	//(2)
	ios_base::fmtflags old = cout.setf(ios_base::right, ios_base::adjustfield);
	cout.setf(old, ios_base::adjustfield);

	//06-谈谈unsetf()     永久     ---置对应的标记为0
	/* void unsetf( fmtflags flags );
	 * Unsets the formatting flags identified by flags.
	 */
	//对于(1)setf
	//cout.setf(ios_base::boolalpha);
	//cout.unsetf(ios_base::boolalpha);
	//对于(2)setf
	cout.setf(ios_base::left, ios_base::adjustfield);	
	cout.setf(0, ios_base::adjustfield);   //设为默认
	cout.unsetf(ios_base::adjustfield);    //设为默认
	
	//07-控制符 存在于<iostream>
	
	//0701-修改显示时使用的技术系统   永久   
	   //默认
	//setf()   (1)
	cout << boolalpha;      //cout.setf(ios_base::boolalpha);
	cout << noboolalpha;    //cout.unsetf(ios_base::boolalpha);
	cout << showbase;       //cout.setf(ios_base::showbase);
	cout << noshowbase;     //cout.unsetf(ios_base::showbase); 
	cout << showpoint;      //cout.setf(ios_base::showpoint);
	cout << noshowpoint;    //cout.unsetf(ios_base::showpoint);
	cout << uppercase;      //cout.setf(ios_base::uppercase);
	cout << nouppercase;    //cout.unsetf(ios_base::uppercase);
	cout << showpos;        //cout.setf(ios_base::showpos); 
	cout << noshowpos;      //cout.unsetf(ios_base::showpos); 

	//setf()   (2)
	//进制
	cout << hex;     //或者  hex(cout);     //等价于cout.setf(ios_base::hex, ios_base::basefield);
	cout << oct;                   //等价于cout.setf(ios_base::oct, ios_base::basefield);
	cout << dec;    //默认         //等价于cout.setf(ios_base::dec, ios_base::basefield);
	//浮点计数
	cout << fixed;             //cout.setf(ios_base::fixed, ios_base::floatfield);
	cout << scientific;        //cout.setf(ios_base::scientific, ios_base::floatfield);
	//对齐方式
	cout << left;              //cout.setf(ios_base::left, ios_base::adjustfield);
	cout << right;             //cout.setf(ios_base::right, ios_base::adjustfield);
	cout << internal;          //cout.setf(ios_base::internal, ios_base::adjustfield);

	return 0;
}