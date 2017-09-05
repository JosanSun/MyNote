#include <iostream>
#include <iomanip>          //setw() setprecision()  setfill()
using namespace std;

//��ʽ�����
int main(int argc, char* argv[])
{
	//01-�����ֶο��     ��ʱ��ֻӰ��������ģ�   streamsize��VS����long long
	/* streamsize width()       //���ص�ǰ��ȣ�Ĭ����0
	 * streamsize width(streamsize i)  //���ÿ��Ϊi,������֮ǰ�Ŀ�� 
	 */
	long long w = cout.width(30);   //0
	w = cout.width();         //30
	w = cout.width();         //30
	cout << 123 << endl;
	w = cout.width();         //0

	cout << setw(12) << 1 << endl;    //����


	//02-����ַ�  Ĭ������ǿո�    ����
	/* CharT fill() const;        (1)ͬwidth
     * CharT fill( CharT ch );    (2)
	 */
	char ch = cout.fill();            
	cout.fill('*');
	cout << setw(10) << 123 << endl;
	cout << setw(10) << 123 << endl;

	cout << setfill('*');

	//03-���ø���������ʾ����          ����
	/* streamsize precision()                      //���ص�ǰ���ȣ�Ĭ����6
	 * streamsize precision(streamsize new_preci)  //���þ���Ϊnew,������֮ǰ�ľ��� 
	 */
	long long prec = cout.precision(12);
	cout << 12.5;
	cout << 25.3;
	prec = cout.precision();

	cout << setprecision(12);

	//04-��ӡĩβ��0��С����
	//ios_base::showpoint��һ��ö��ֵ����̬����
	//static constexpr _Fmtflags showpoint = (_Fmtflags)_IOSshowpoint;
	cout.setf(ios_base::showpoint);
	cout << 2.0 << endl;         //����cout.setf(ios_base::showpoint); ��ʾΪ2���ӵĻ�����ʾΪ2.00000
	cout << 2 << endl;           //�ӻ��߲��Ӷ���2, ���ۣ�����������ʾ����
	cout << 20000.0 << endl;     //��ʾ20000.0
	cout << 200000.0 << endl;    //��ʾ200000.
	cout << 2000000.0 << endl;   //2.00000e+06
	cout << fixed << 2000000.0 << endl;   //2000000.000000  ò���������λ������prec�Ļ���С���������ʾprec��
	//05-��̸setf()        ����   ---�ö�Ӧ�ı��Ϊ1
	/* fmtflags VS����int
	 * fmtflags setf( fmtflags flags );  (1) 
	 * fmtflags setf( fmtflags flags, fmtflags mask );  (2)  //���õ�maskֻ��3��basefield�� adjustfield�� floatfield
	 */
	// (1) --------------------------
	cout.setf(ios_base::boolalpha);   //��ʾtrue false,  not 0 or 1
	cout.setf(ios_base::showbase);    //��ʾ����ǰ׺0, 0x
	cout.setf(ios_base::showpoint);   //��ʾĩβ��С����
	cout.setf(ios_base::uppercase);   //��ʾ16���ƴ�д���Լ�E
	cout.setf(ios_base::showpos);     //����ǰ����ϡ�+��

	// (2) ---------------------------
	//����
	cout.setf(ios_base::dec, ios_base::basefield);   //Ĭ��
	cout.setf(ios_base::oct, ios_base::basefield);
	cout.setf(ios_base::hex, ios_base::basefield);

	//����������    û��ר��ָʾ������Ĭ����ʾģʽ�ı��
	cout.setf(ios_base::fixed, ios_base::floatfield);      //���������  
	cout.setf(ios_base::scientific, ios_base::floatfield); //��ѧ
	cout.setf(0, ios_base::floatfield);    //Ĭ��

	//�������
	cout.setf(ios_base::left, ios_base::adjustfield);
	cout.setf(ios_base::right, ios_base::adjustfield);      //Ĭ��
	cout.setf(ios_base::internal, ios_base::adjustfield);   //���Ż��߻���ǰ׺����룬ֵ�Ҷ���
	
	//��λָ�����
	//(1)
	ios_base::fmtflags old = cout.setf(ios_base::showbase);
	cout.setf(old);
	//(2)
	ios_base::fmtflags old = cout.setf(ios_base::right, ios_base::adjustfield);
	cout.setf(old, ios_base::adjustfield);

	//06-̸̸unsetf()     ����     ---�ö�Ӧ�ı��Ϊ0
	/* void unsetf( fmtflags flags );
	 * Unsets the formatting flags identified by flags.
	 */
	//����(1)setf
	//cout.setf(ios_base::boolalpha);
	//cout.unsetf(ios_base::boolalpha);
	//����(2)setf
	cout.setf(ios_base::left, ios_base::adjustfield);	
	cout.setf(0, ios_base::adjustfield);   //��ΪĬ��
	cout.unsetf(ios_base::adjustfield);    //��ΪĬ��
	
	//07-���Ʒ� ������<iostream>
	
	//0701-�޸���ʾʱʹ�õļ���ϵͳ   ����   
	   //Ĭ��
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
	//����
	cout << hex;     //����  hex(cout);     //�ȼ���cout.setf(ios_base::hex, ios_base::basefield);
	cout << oct;                   //�ȼ���cout.setf(ios_base::oct, ios_base::basefield);
	cout << dec;    //Ĭ��         //�ȼ���cout.setf(ios_base::dec, ios_base::basefield);
	//�������
	cout << fixed;             //cout.setf(ios_base::fixed, ios_base::floatfield);
	cout << scientific;        //cout.setf(ios_base::scientific, ios_base::floatfield);
	//���뷽ʽ
	cout << left;              //cout.setf(ios_base::left, ios_base::adjustfield);
	cout << right;             //cout.setf(ios_base::right, ios_base::adjustfield);
	cout << internal;          //cout.setf(ios_base::internal, ios_base::adjustfield);

	return 0;
}