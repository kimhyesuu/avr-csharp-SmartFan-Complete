namespace serial
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.button2 = new System.Windows.Forms.Button();
            this.progressBar3_motor1 = new System.Windows.Forms.ProgressBar();
            this.progressBar2_end = new System.Windows.Forms.ProgressBar();
            this.button2_end = new System.Windows.Forms.Button();
            this.button3_mootor3 = new System.Windows.Forms.Button();
            this.button2_motor2 = new System.Windows.Forms.Button();
            this.button2_motor1 = new System.Windows.Forms.Button();
            this.progressBar2_motor1 = new System.Windows.Forms.ProgressBar();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.button4_send = new System.Windows.Forms.Button();
            this.textBox1_senddata = new System.Windows.Forms.TextBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.button3_clear = new System.Windows.Forms.Button();
            this.textBox1_receivedata = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.label2_comport = new System.Windows.Forms.Label();
            this.button2_close = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.combox_BPS = new System.Windows.Forms.ComboBox();
            this.combox_Port = new System.Windows.Forms.ComboBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label3_time = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Stencil", 28.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(392, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(284, 57);
            this.label1.TabIndex = 0;
            this.label1.Text = "Smart FAN";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(12, 57);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1050, 447);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox8);
            this.tabPage1.Controls.Add(this.groupBox7);
            this.tabPage1.Controls.Add(this.groupBox6);
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Font = new System.Drawing.Font("MoeumT R", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(1042, 418);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "setup";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.button2);
            this.groupBox8.Controls.Add(this.progressBar3_motor1);
            this.groupBox8.Controls.Add(this.progressBar2_end);
            this.groupBox8.Controls.Add(this.button2_end);
            this.groupBox8.Controls.Add(this.button3_mootor3);
            this.groupBox8.Controls.Add(this.button2_motor2);
            this.groupBox8.Controls.Add(this.button2_motor1);
            this.groupBox8.Controls.Add(this.progressBar2_motor1);
            this.groupBox8.Location = new System.Drawing.Point(326, 254);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(697, 158);
            this.groupBox8.TabIndex = 3;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "FAN CONTROL";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(6, 58);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(68, 58);
            this.button2.TabIndex = 9;
            this.button2.Text = "수동";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click_2);
            // 
            // progressBar3_motor1
            // 
            this.progressBar3_motor1.Location = new System.Drawing.Point(222, 24);
            this.progressBar3_motor1.Name = "progressBar3_motor1";
            this.progressBar3_motor1.Size = new System.Drawing.Size(395, 14);
            this.progressBar3_motor1.TabIndex = 8;
            // 
            // progressBar2_end
            // 
            this.progressBar2_end.Location = new System.Drawing.Point(80, 24);
            this.progressBar2_end.Name = "progressBar2_end";
            this.progressBar2_end.Size = new System.Drawing.Size(112, 14);
            this.progressBar2_end.TabIndex = 8;
            // 
            // button2_end
            // 
            this.button2_end.Location = new System.Drawing.Point(80, 58);
            this.button2_end.Name = "button2_end";
            this.button2_end.Size = new System.Drawing.Size(112, 58);
            this.button2_end.TabIndex = 7;
            this.button2_end.Text = "중지";
            this.button2_end.UseVisualStyleBackColor = true;
            this.button2_end.Click += new System.EventHandler(this.button2_Click_1);
            // 
            // button3_mootor3
            // 
            this.button3_mootor3.Location = new System.Drawing.Point(505, 58);
            this.button3_mootor3.Name = "button3_mootor3";
            this.button3_mootor3.Size = new System.Drawing.Size(112, 58);
            this.button3_mootor3.TabIndex = 6;
            this.button3_mootor3.Text = "강풍";
            this.button3_mootor3.UseVisualStyleBackColor = true;
            this.button3_mootor3.Click += new System.EventHandler(this.button3_mootor3_Click);
            // 
            // button2_motor2
            // 
            this.button2_motor2.Location = new System.Drawing.Point(367, 58);
            this.button2_motor2.Name = "button2_motor2";
            this.button2_motor2.Size = new System.Drawing.Size(112, 58);
            this.button2_motor2.TabIndex = 5;
            this.button2_motor2.Text = "중풍";
            this.button2_motor2.UseVisualStyleBackColor = true;
            this.button2_motor2.Click += new System.EventHandler(this.button2_motor2_Click);
            // 
            // button2_motor1
            // 
            this.button2_motor1.Location = new System.Drawing.Point(222, 58);
            this.button2_motor1.Name = "button2_motor1";
            this.button2_motor1.Size = new System.Drawing.Size(112, 58);
            this.button2_motor1.TabIndex = 4;
            this.button2_motor1.Text = "미풍";
            this.button2_motor1.UseVisualStyleBackColor = true;
            this.button2_motor1.Click += new System.EventHandler(this.button2_motor1_Click);
            // 
            // progressBar2_motor1
            // 
            this.progressBar2_motor1.Location = new System.Drawing.Point(80, 24);
            this.progressBar2_motor1.Name = "progressBar2_motor1";
            this.progressBar2_motor1.Size = new System.Drawing.Size(112, 14);
            this.progressBar2_motor1.TabIndex = 0;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.button4_send);
            this.groupBox7.Controls.Add(this.textBox1_senddata);
            this.groupBox7.Location = new System.Drawing.Point(326, 178);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(697, 70);
            this.groupBox7.TabIndex = 2;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "senddata";
            // 
            // button4_send
            // 
            this.button4_send.Location = new System.Drawing.Point(562, 24);
            this.button4_send.Name = "button4_send";
            this.button4_send.Size = new System.Drawing.Size(123, 26);
            this.button4_send.TabIndex = 1;
            this.button4_send.Text = "send";
            this.button4_send.UseVisualStyleBackColor = true;
            this.button4_send.Click += new System.EventHandler(this.button4_send_Click);
            // 
            // textBox1_senddata
            // 
            this.textBox1_senddata.Location = new System.Drawing.Point(6, 24);
            this.textBox1_senddata.Multiline = true;
            this.textBox1_senddata.Name = "textBox1_senddata";
            this.textBox1_senddata.Size = new System.Drawing.Size(537, 26);
            this.textBox1_senddata.TabIndex = 2;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.button3_clear);
            this.groupBox6.Controls.Add(this.textBox1_receivedata);
            this.groupBox6.Location = new System.Drawing.Point(326, 6);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(697, 164);
            this.groupBox6.TabIndex = 1;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "receivedata";
            // 
            // button3_clear
            // 
            this.button3_clear.Location = new System.Drawing.Point(562, 24);
            this.button3_clear.Name = "button3_clear";
            this.button3_clear.Size = new System.Drawing.Size(123, 33);
            this.button3_clear.TabIndex = 1;
            this.button3_clear.Text = "Clear";
            this.button3_clear.UseVisualStyleBackColor = true;
            // 
            // textBox1_receivedata
            // 
            this.textBox1_receivedata.Location = new System.Drawing.Point(15, 24);
            this.textBox1_receivedata.Multiline = true;
            this.textBox1_receivedata.Name = "textBox1_receivedata";
            this.textBox1_receivedata.Size = new System.Drawing.Size(528, 120);
            this.textBox1_receivedata.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox5);
            this.groupBox1.Controls.Add(this.button2_close);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.progressBar1);
            this.groupBox1.Controls.Add(this.combox_BPS);
            this.groupBox1.Controls.Add(this.combox_Port);
            this.groupBox1.Controls.Add(this.groupBox4);
            this.groupBox1.Controls.Add(this.groupBox3);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Location = new System.Drawing.Point(6, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(304, 242);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "setup";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.label2_comport);
            this.groupBox5.Location = new System.Drawing.Point(169, 148);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(106, 83);
            this.groupBox5.TabIndex = 1;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "comport";
            // 
            // label2_comport
            // 
            this.label2_comport.AutoSize = true;
            this.label2_comport.Font = new System.Drawing.Font("MoeumT R", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label2_comport.Location = new System.Drawing.Point(28, 30);
            this.label2_comport.Name = "label2_comport";
            this.label2_comport.Size = new System.Drawing.Size(53, 34);
            this.label2_comport.TabIndex = 1;
            this.label2_comport.Text = "off";
            // 
            // button2_close
            // 
            this.button2_close.Location = new System.Drawing.Point(14, 197);
            this.button2_close.Name = "button2_close";
            this.button2_close.Size = new System.Drawing.Size(81, 34);
            this.button2_close.TabIndex = 3;
            this.button2_close.Text = "closeport";
            this.button2_close.UseVisualStyleBackColor = true;
            this.button2_close.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(15, 160);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(81, 31);
            this.button1.TabIndex = 3;
            this.button1.Text = "openport";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(169, 117);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(106, 23);
            this.progressBar1.TabIndex = 2;
            // 
            // combox_BPS
            // 
            this.combox_BPS.FormattingEnabled = true;
            this.combox_BPS.Items.AddRange(new object[] {
            "9600",
            "115200"});
            this.combox_BPS.Location = new System.Drawing.Point(169, 74);
            this.combox_BPS.Name = "combox_BPS";
            this.combox_BPS.Size = new System.Drawing.Size(106, 25);
            this.combox_BPS.TabIndex = 1;
            // 
            // combox_Port
            // 
            this.combox_Port.FormattingEnabled = true;
            this.combox_Port.Location = new System.Drawing.Point(169, 34);
            this.combox_Port.Name = "combox_Port";
            this.combox_Port.Size = new System.Drawing.Size(106, 25);
            this.combox_Port.TabIndex = 1;
            this.combox_Port.SelectedIndexChanged += new System.EventHandler(this.combox_Port_SelectedIndexChanged);
            // 
            // groupBox4
            // 
            this.groupBox4.Location = new System.Drawing.Point(14, 116);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(104, 24);
            this.groupBox4.TabIndex = 0;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "portstatus";
            // 
            // groupBox3
            // 
            this.groupBox3.Location = new System.Drawing.Point(14, 73);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(82, 24);
            this.groupBox3.TabIndex = 0;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "BPS";
            // 
            // groupBox2
            // 
            this.groupBox2.Location = new System.Drawing.Point(14, 33);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(82, 24);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "PORT";
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 25);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(1042, 418);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "control";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabPage3
            // 
            this.tabPage3.Location = new System.Drawing.Point(4, 25);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(1042, 418);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "monitoring";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // tabPage4
            // 
            this.tabPage4.Location = new System.Drawing.Point(4, 25);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage4.Size = new System.Drawing.Size(1042, 418);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "history";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label3_time
            // 
            this.label3_time.AutoSize = true;
            this.label3_time.Location = new System.Drawing.Point(959, 59);
            this.label3_time.Name = "label3_time";
            this.label3_time.Size = new System.Drawing.Size(0, 15);
            this.label3_time.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1074, 516);
            this.Controls.Add(this.label3_time);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "serialco";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button2_close;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.ComboBox combox_BPS;
        private System.Windows.Forms.ComboBox combox_Port;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label2_comport;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Button button4_send;
        private System.Windows.Forms.TextBox textBox1_senddata;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Button button3_clear;
        private System.Windows.Forms.TextBox textBox1_receivedata;
        private System.Windows.Forms.Label label3_time;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Button button2_motor1;
        private System.Windows.Forms.Button button3_mootor3;
        private System.Windows.Forms.Button button2_motor2;
        private System.Windows.Forms.ProgressBar progressBar2_motor1;
        private System.Windows.Forms.Button button2_end;
        private System.Windows.Forms.ProgressBar progressBar3_motor1;
        private System.Windows.Forms.ProgressBar progressBar2_end;
        private System.Windows.Forms.Button button2;
    }
}

