/*
The following program is designed to find every possible reachable point of a robotic arm based upon specifications given it such as types of joints and lengths

*/
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

/*void* Reset(double long* input)
{
input[0]=0;
//input[1]=0;
//input[2]=0;
//input[3]=1.0;
return input;
}*/
void Rotate_x(float* input, float &theta)
{
	float input1 = input[1];
	//input[0]=input[0];
	input[1] = cos(theta)*input[1] - sin(theta)*input[2];
	input[2] = sin(theta)*input1 + cos(theta)*input[2];
	//input[3]=input[3];
}

void Rotate_y(float* input, float &theta)
{
	float input0 = input[0];
	input[0] = cos(theta)*input[0] + sin(theta)*input[2];
	//input[1]=input[1];
	input[2] = -sin(theta)*input0 + cos(theta)*input[2];
	//input[3]=input[3];
}

void Rotate_z(float* input, float &theta)
{
	float input0 = input[0];
	input[0] = cos(theta)*input[0] - sin(theta)*input[1];
	input[1] = sin(theta)*input0 + cos(theta)*input[1];
	//input[2]=input[2];
	//input[3]=input[3];
}

void Translate(float* input, float &length, float* test)
{
	test[0] = input[0] + length*input[3];
	test[1] = input[1];
	test[2] = input[2];
	test[3] = 1.0;
	//return input;
}

int main()
{
	float Length[7] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
	float angle;
	cout << "Enter the Lengths and types of joint in txt file then enter start angle\n";
	cin >> angle;
	//read in data
	ifstream input;
	stringstream ss;
	input.open("specs.txt");
	int j = 0;
	string entry;
	while (input >> entry)
	{
		ss << entry;
		ss >> Length[j];
		ss.clear();
		j++;
	}
	input.close();
	static float reach1 = Length[3] + Length[4] + Length[5] + Length[6];
	static float reach2 = Length[4] + Length[5] + Length[6];
	static float reach3 = Length[5] + Length[6];
	float reach4 = Length[6];
	//string output1;
	//initialize
	//double long theta[6]={0,0,0,0,0,0}; changed to
	float theta[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

	float Start[4] = { 0, Length[0], 0, 1 };
	float Stage[4] = { 0, 0, 0, 1.0 };
	//double* test;
	ss << angle;
	string name;
	int check = 1;
	int check1 = 1;
	ss >> name;
	name = name + "test2all3deg20in.csv";
	//double check[2];
	//double diff[2];
	float total1[4];
	float total2[4];
	float total3[4];
	float total4[4];
	float total5[4];
	float total6[4];
	float test[4];
	ofstream output(name);
	int count = 0;
	int count2 = 0;
	int step = 3;
	float plane1 = 19.9;
	float plane2 = plane1 + 0.1;
	static float stepratio = step*3.14 / 180;
	static float ratio = 3.14 / 180;
	float thetar[6] = { angle*ratio, 0.0, -135.0*ratio, 0.0, -135.0*ratio, 0.0 };
	//double countmax=pow((360/step),5);
	int countmax = 180.0 / step * 135 / step;
	cout << countmax << " ";
	theta[0] = thetar[0];
	for (int i = 0; i <= 180; i = i + step) //Theta 1
	{
		//Stage 1
		//Reset(Start);
		Translate(Start, Length[1], test);
		Rotate_y(test, theta[0]);
		total1[0] = test[0];
		total1[1] = test[1];
		total1[2] = test[2];
		total1[3] = test[3];
		theta[1] = 0;
		for (int i2 = 0; i2 <= 135; i2 = i2 + step) //Theta 2
		{
			//Stage 2
			//Reset(Stage);
			Translate(Stage, Length[2], test);
			Rotate_z(test, theta[1]);
			Rotate_y(test, theta[0]);
			total2[0] = total1[0] + test[0];
			total2[1] = total1[1] + test[1];
			total2[2] = total1[2] + test[2];
			total2[3] = total1[3] + test[3];
			theta[2] = thetar[2];
			for (int i3 = 0; i3 <= 270; i3 = i3 + step) //Theta 3
			{
				//check1=1;
				//Stage 3
				float test2[4];
				if (plane2<(total2[0]) || plane1>(total2[0] + reach1)) //(15.0<(total2[0]-reach1) || 14.9>(total2[0]+reach1))
				{
					break;
				}
				//Reset(Stage);
				Translate(Stage, Length[3], test2);
				Rotate_z(test2, theta[2]);
				Rotate_z(test2, theta[1]);
				Rotate_y(test2, theta[0]);
				total3[0] = total2[0] + test2[0];
				total3[1] = total2[1] + test2[1];
				total3[2] = total2[2] + test2[2];
				total3[3] = total2[3] + test2[3];
				theta[3] = 0;
				for (int i4 = 0; i4 <= 360; i4 = i4 + step) //Theta 4
				{
					//Stage 4
					if (plane2<(total3[0]) || plane1>(total3[0] + reach2)) //(15.0<(total3[0] -reach2) || 14.9>(total3[0]+reach2))
					{
						break;
					}
					//Reset(Stage);
					Translate(Stage, Length[4], test2);
					Rotate_x(test2, theta[3]);
					Rotate_z(test2, theta[2]);
					Rotate_z(test2, theta[1]);
					Rotate_y(test2, theta[0]);
					total4[0] = total3[0] + test2[0];
					total4[1] = total3[1] + test2[1];
					total4[2] = total3[2] + test2[2];
					total4[3] = total3[3] + test2[3];
					theta[4] = thetar[4];

					if (plane2<(total4[0]) || plane1>(total4[0] + reach3)) //(15.0<(total3[0] -reach2) || 14.9>(total3[0]+reach2))
					{
						break;
					}
					for (int i5 = 0; i5 <= 270; i5 = i5 + step) //Theta 5
					{
						/*float total[4];
						float test[4];
						//Stage 1
						//Reset(Start);
						Translate(Start,Length[1],test);
						Rotate_y(test,theta[0]);
						total[0]=test[0];
						total[1]=test[1];
						total[2]=test[2];
						total[3]=test[3];
						//Stage 2
						//Reset(Stage);
						Translate(Stage,Length[2],test);
						Rotate_z(test,theta[1]);
						Rotate_y(test,theta[0]);
						total[0]=total[0]+test[0];
						total[1]=total[1]+test[1];
						total[2]=total[2]+test[2];
						total[3]=total[3]+test[3];
						//Stage 3
						if (15.0<(total[0]-reach1) || 14.9>(total[0]+reach1))
						{
						check1=0;
						break;
						}
						//Reset(Stage);
						Translate(Stage,Length[3],test);
						Rotate_z(test,theta[2]);
						Rotate_z(test,theta[1]);
						Rotate_y(test,theta[0]);
						total[0]=total[0]+test[0];
						total[1]=total[1]+test[1];
						total[2]=total[2]+test[2];
						total[3]=total[3]+test[3];
						//Stage 4
						if (15.0<(total[0]-reach2) || 14.9>(total[0]+reach2))
						{
						check=0;
						break;
						}
						//Reset(Stage);
						Translate(Stage,Length[4],test);
						Rotate_x(test,theta[3]);
						Rotate_z(test,theta[2]);
						Rotate_z(test,theta[1]);
						Rotate_y(test,theta[0]);
						total[0]=total[0]+test[0];
						total[1]=total[1]+test[1];
						total[2]=total[2]+test[2];
						total[3]=total[3]+test[3];
						//Stage 5
						if (15.0<(total[0]-reach3) || 14.9>(total[0]+reach3))
						{
						check=0;
						break;
						}*/
						//Reset(Stage);
						Translate(Stage, Length[5], test2);
						Rotate_z(test2, theta[4]);
						Rotate_x(test2, theta[3]);
						Rotate_z(test2, theta[2]);
						Rotate_z(test2, theta[1]);
						Rotate_y(test2, theta[0]);
						total5[0] = total4[0] + test2[0];
						total5[1] = total4[1] + test2[1];
						total5[2] = total4[2] + test2[2];
						total5[3] = total4[3] + test2[3];
						//Stage 6
						//Reset(Stage)	
						//float set2a=total[0]-reach4;
						//float set2b=total[0]+reach4;
						//set3=set2-reach4;
						//if(set2a > 15.0 || 14.9>set2b)
						if (plane2>(total5[0]) && plane1<(total5[0] + reach4)) //(15.0>(total5[0]-reach4) && 14.9<(total5[0]+reach4))
						{
							Translate(Stage, Length[6], test2);
							Rotate_x(test2, theta[5]);
							Rotate_z(test2, theta[4]);
							Rotate_x(test2, theta[3]);
							Rotate_z(test2, theta[2]);
							Rotate_z(test2, theta[1]);
							Rotate_y(test2, theta[0]);

							total6[0] = total5[0] + test2[0];
							total6[1] = total5[1] + test2[1];
							total6[2] = total5[2] + test2[2];
							//total[3]=total[3]+test[3];		
							//Output
							if (total6[0]>plane1 && total6[0]<plane2)
							{
								if (abs(test2[1])<.01 && abs(test2[2])<.01)
								{

									output << total6[0] << ",";
									output << total6[1] << ", ";
									output << total6[2] << ", ";
									count++;
									if ((count + 1) % 6 == 0)
									{
										count = 0;
										output << "\n";
									}
								}
							}
						}
						theta[4] = theta[4] + stepratio;
					}
					theta[3] = theta[3] + stepratio;
				}
				theta[2] = theta[2] + stepratio;
			}
			count2++;
			theta[1] = theta[1] + stepratio;
			cout << count2*100.0 / countmax << "percent\n";
		}
		//cout<<i/360<<"percent\n";
		theta[0] = theta[0] + stepratio;
	}
	output.close();
	system("pause");
	return 0;
}