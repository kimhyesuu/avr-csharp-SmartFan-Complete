using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports; //Add
namespace serial
{
    public partial class Form1 : Form //퍼블릭 펑션 안에 
    {
        string dataIN; //add comport로부터의 data string 변수
        string[] inputsensordata; //Add
        int time_value;//add timer 변수
        int flag = 0;
        public Form1()
        {
            InitializeComponent();
            getAvailableports(); //add combobox 뿌려주는 역할
        }
        //add comport list 가져 오는 함수
        void getAvailableports()
        {
            string[] ports = SerialPort.GetPortNames();
            combox_Port.Items.AddRange(ports);
        }
        //open port
        private void button1_Click(object sender, EventArgs e)
        {
            //----------------add start
            try
            {
                if (combox_Port.Text == "" || combox_BPS.Text == "")
                {
                    textBox1_receivedata.Text = "please select port setting";
                    //모아쓰기지원이 가능하니깐 쓰자
                }
                else
                {
                    serialPort1.PortName = combox_Port.Text;
                    //1. i = atoi(string); 아스키 -> int로 변환
                    serialPort1.BaudRate = Convert.ToInt32(combox_BPS.Text); //atoi와 동일
                    //2. 해당 comport를 open한다.
                    serialPort1.Open();
                    //fail시 상황을 염두하고 if문 사용한다.
                    progressBar1.Value = 100;
                    label2_comport.Text = "ON"; //off였던 부분을 on으로 바꿔주는 역할
                    button4_send.Enabled = true;
                    button3_clear.Enabled = true;
                    button2_close.Enabled = true; // close button
                    button1.Enabled = false;
                    //add를 해야 함

                    button4_send.Enabled = true;
                    textBox1_senddata.Enabled = true;
                }
            }
            catch (UnauthorizedAccessException) // 예외 상황 처리
            {
                //문제가 발생하면 여기로 들어온다.
                textBox1_receivedata.Text = "Exception case Occurs!!!!";
            }
            //----------------add end
        }
        //close port
        private void button2_Click(object sender, EventArgs e)
        {
            //----------------add start
            serialPort1.Close(); // comport의 해제한다.
            progressBar1.Value = 0;
            label2_comport.Text = "OFF"; //ON였던 부분을 OFF으로 바꿔주는 역할
            button3_clear.Enabled = false;
            button4_send.Enabled = false;
            button2_close.Enabled = false; // close button
            button1.Enabled = true;
            textBox1_senddata.Enabled = true;
            //----------------add end
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        //ADD 이곳으로 AVR로부터 RX DATA가 오면 CALL BACK FUNCTION이 자동 수행되는 것
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            dataIN = serialPort1.ReadLine(); //하드웨어있는 버퍼(data)를 다 읽는것 \r\n만날때까지 
            // dataIN = serialPort1.ReadLine(); 둘 중 하나 써도 괜찮다. \n을 만날때까지 읽는 것
            this.Invoke(new EventHandler(ShowData));
        }
        //add avr로부터 data를 수신창에 디스플레이한다.
        private void ShowData(object sender, EventArgs e)
        {
            //in되면
            //send 버튼을 눌렀을 때 데이터가 입력된 부분을 처리 --> 이 부분 필터링한다.
            textBox1_receivedata.Text += dataIN + Environment.NewLine;
           
        }
        //add pc --> avr로 data를 보내는 function
        private void button4_send_Click(object sender, EventArgs e)
        {
            //add start
            string command = textBox1_senddata.Text; //add senddata를 variable 저장 후 variable 핸들링한다.
            if (command.Length > 0) //입력을 했다.
            {
                serialPort1.WriteLine(command + Environment.NewLine);//Environment.NewLine == \n
                                                                     //\n이 컴터가 자동적으로 하지않아서 내가 직접 설정
                                                                     //textBox1_senddata.Text를 avr로 송신
                textBox1_senddata.Text = "";//textBox1_senddata창을 clear
            }
            //add end
        }

        //timer tick event 발생시 터지는 것
        private void timer1_Tick(object sender, EventArgs e)
        {
            //타이머 인터럽트
            label3_time.Text = DateTime.Now.ToLongTimeString();
        }
        private void button2_motor1_Click(object sender, EventArgs e)
        {
            progressBar3_motor1.Value = 30;//프로그래스 전체를 다 그려라
            progressBar2_end.Value = 0;                           
            serialPort1.WriteLine("motorona" + Environment.NewLine);//Environment.NewLine == \n
            //여기서 atmel에서 작성한 값을 여기서 메크로형식처럼 쓰는 것입니다.
            textBox1_senddata.Text = "motorona" + Environment.NewLine;
        }
        private void button2_Click_1(object sender, EventArgs e)
        {
            progressBar2_end.Value = 100;
            progressBar3_motor1.Value = 0;//프로그래스 전체를 다 그려라         
            serialPort1.WriteLine("motoroff" + Environment.NewLine);//Environment.NewLine == \n
            //여기서 atmel에서 작성한 값을 여기서 메크로형식처럼 쓰는 것입니다.
            textBox1_senddata.Text = "motoroff" + Environment.NewLine;
        }

        private void button2_motor2_Click(object sender, EventArgs e)
        {        
            progressBar2_end.Value = 0;
            progressBar3_motor1.Value = 70;//프로그래스 전체를 다 그려라    
           
            serialPort1.WriteLine("motoronb" + Environment.NewLine);//Environment.NewLine == \n
            //여기서 atmel에서 작성한 값을 여기서 메크로형식처럼 쓰는 것입니다.
            textBox1_senddata.Text = "motoronb" + Environment.NewLine;
        }

        private void button3_mootor3_Click(object sender, EventArgs e)
        {
           
            progressBar2_end.Value = 0;
            progressBar3_motor1.Value = 100;//프로그래스 전체를 다 그려라          
            serialPort1.WriteLine("motoronc" + Environment.NewLine);//Environment.NewLine == \n
            //여기서 atmel에서 작성한 값을 여기서 메크로형식처럼 쓰는 것입니다.
            textBox1_senddata.Text = "motoronc" + Environment.NewLine;
        }

        private void button2_Click_2(object sender, EventArgs e)
        {               
            serialPort1.WriteLine("rotate" + Environment.NewLine);//Environment.NewLine == \n
            //여기서 atmel에서 작성한 값을 여기서 메크로형식처럼 쓰는 것입니다.
            textBox1_senddata.Text = "rotate" + Environment.NewLine;
        }

        private void combox_Port_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
