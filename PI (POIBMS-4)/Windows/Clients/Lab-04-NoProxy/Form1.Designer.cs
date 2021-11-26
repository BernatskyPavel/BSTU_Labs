
namespace Lab_04_NoProxy
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Send = new System.Windows.Forms.Button();
            this.A1_S = new System.Windows.Forms.TextBox();
            this.A1_K = new System.Windows.Forms.TextBox();
            this.A1_F = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.A2_F = new System.Windows.Forms.TextBox();
            this.A2_K = new System.Windows.Forms.TextBox();
            this.A2_S = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.Result_F = new System.Windows.Forms.TextBox();
            this.Result_K = new System.Windows.Forms.TextBox();
            this.Result_S = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.A1_F_Err = new System.Windows.Forms.Label();
            this.A1_K_Err = new System.Windows.Forms.Label();
            this.A2_K_Err = new System.Windows.Forms.Label();
            this.A2_F_Err = new System.Windows.Forms.Label();
            this.clear = new System.Windows.Forms.Button();
            this.Error_Label = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Send
            // 
            this.Send.Location = new System.Drawing.Point(200, 232);
            this.Send.Name = "Send";
            this.Send.Size = new System.Drawing.Size(100, 25);
            this.Send.TabIndex = 0;
            this.Send.Text = "Send";
            this.Send.UseVisualStyleBackColor = true;
            this.Send.Click += new System.EventHandler(this.Send_Click);
            // 
            // A1_S
            // 
            this.A1_S.Location = new System.Drawing.Point(46, 52);
            this.A1_S.Name = "A1_S";
            this.A1_S.Size = new System.Drawing.Size(100, 20);
            this.A1_S.TabIndex = 1;
            // 
            // A1_K
            // 
            this.A1_K.Location = new System.Drawing.Point(46, 109);
            this.A1_K.Name = "A1_K";
            this.A1_K.Size = new System.Drawing.Size(100, 20);
            this.A1_K.TabIndex = 2;
            this.A1_K.TextChanged += new System.EventHandler(this.A1_K_TextChanged);
            // 
            // A1_F
            // 
            this.A1_F.Location = new System.Drawing.Point(46, 166);
            this.A1_F.Name = "A1_F";
            this.A1_F.Size = new System.Drawing.Size(100, 20);
            this.A1_F.TabIndex = 3;
            this.A1_F.TextChanged += new System.EventHandler(this.A1_F_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 55);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "S";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(26, 112);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(14, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "K";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(27, 169);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(13, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "F";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(181, 169);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(13, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "F";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(180, 112);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(14, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "K";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(180, 55);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(14, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "S";
            // 
            // A2_F
            // 
            this.A2_F.Location = new System.Drawing.Point(200, 166);
            this.A2_F.Name = "A2_F";
            this.A2_F.Size = new System.Drawing.Size(100, 20);
            this.A2_F.TabIndex = 9;
            this.A2_F.TextChanged += new System.EventHandler(this.A2_F_TextChanged);
            // 
            // A2_K
            // 
            this.A2_K.Location = new System.Drawing.Point(200, 109);
            this.A2_K.Name = "A2_K";
            this.A2_K.Size = new System.Drawing.Size(100, 20);
            this.A2_K.TabIndex = 8;
            this.A2_K.TextChanged += new System.EventHandler(this.A2_K_TextChanged);
            // 
            // A2_S
            // 
            this.A2_S.Location = new System.Drawing.Point(200, 52);
            this.A2_S.Name = "A2_S";
            this.A2_S.Size = new System.Drawing.Size(100, 20);
            this.A2_S.TabIndex = 7;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(340, 169);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(13, 13);
            this.label7.TabIndex = 18;
            this.label7.Text = "F";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(339, 112);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(14, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "K";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(339, 55);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(14, 13);
            this.label9.TabIndex = 16;
            this.label9.Text = "S";
            // 
            // Result_F
            // 
            this.Result_F.Location = new System.Drawing.Point(359, 166);
            this.Result_F.Name = "Result_F";
            this.Result_F.ReadOnly = true;
            this.Result_F.Size = new System.Drawing.Size(100, 20);
            this.Result_F.TabIndex = 15;
            // 
            // Result_K
            // 
            this.Result_K.Location = new System.Drawing.Point(359, 109);
            this.Result_K.Name = "Result_K";
            this.Result_K.ReadOnly = true;
            this.Result_K.Size = new System.Drawing.Size(100, 20);
            this.Result_K.TabIndex = 14;
            // 
            // Result_S
            // 
            this.Result_S.Location = new System.Drawing.Point(359, 52);
            this.Result_S.Name = "Result_S";
            this.Result_S.ReadOnly = true;
            this.Result_S.Size = new System.Drawing.Size(100, 20);
            this.Result_S.TabIndex = 13;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(83, 26);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(20, 13);
            this.label10.TabIndex = 19;
            this.label10.Text = "A1";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(238, 26);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(20, 13);
            this.label11.TabIndex = 20;
            this.label11.Text = "A2";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(391, 26);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(37, 13);
            this.label12.TabIndex = 21;
            this.label12.Text = "Result";
            // 
            // A1_F_Err
            // 
            this.A1_F_Err.AutoSize = true;
            this.A1_F_Err.ForeColor = System.Drawing.Color.Red;
            this.A1_F_Err.Location = new System.Drawing.Point(43, 189);
            this.A1_F_Err.Name = "A1_F_Err";
            this.A1_F_Err.Size = new System.Drawing.Size(104, 13);
            this.A1_F_Err.TabIndex = 22;
            this.A1_F_Err.Text = "Неверный формат!";
            this.A1_F_Err.Visible = false;
            // 
            // A1_K_Err
            // 
            this.A1_K_Err.AutoSize = true;
            this.A1_K_Err.ForeColor = System.Drawing.Color.Red;
            this.A1_K_Err.Location = new System.Drawing.Point(43, 132);
            this.A1_K_Err.Name = "A1_K_Err";
            this.A1_K_Err.Size = new System.Drawing.Size(104, 13);
            this.A1_K_Err.TabIndex = 23;
            this.A1_K_Err.Text = "Неверный формат!";
            this.A1_K_Err.Visible = false;
            // 
            // A2_K_Err
            // 
            this.A2_K_Err.AutoSize = true;
            this.A2_K_Err.ForeColor = System.Drawing.Color.Red;
            this.A2_K_Err.Location = new System.Drawing.Point(197, 132);
            this.A2_K_Err.Name = "A2_K_Err";
            this.A2_K_Err.Size = new System.Drawing.Size(104, 13);
            this.A2_K_Err.TabIndex = 25;
            this.A2_K_Err.Text = "Неверный формат!";
            this.A2_K_Err.Visible = false;
            // 
            // A2_F_Err
            // 
            this.A2_F_Err.AutoSize = true;
            this.A2_F_Err.ForeColor = System.Drawing.Color.Red;
            this.A2_F_Err.Location = new System.Drawing.Point(197, 189);
            this.A2_F_Err.Name = "A2_F_Err";
            this.A2_F_Err.Size = new System.Drawing.Size(104, 13);
            this.A2_F_Err.TabIndex = 24;
            this.A2_F_Err.Text = "Неверный формат!";
            this.A2_F_Err.Visible = false;
            // 
            // clear
            // 
            this.clear.Location = new System.Drawing.Point(359, 232);
            this.clear.Name = "clear";
            this.clear.Size = new System.Drawing.Size(100, 25);
            this.clear.TabIndex = 0;
            this.clear.Text = "Clear";
            this.clear.UseVisualStyleBackColor = true;
            this.clear.Click += new System.EventHandler(this.clear_Click);
            // 
            // Error_Label
            // 
            this.Error_Label.AutoSize = true;
            this.Error_Label.ForeColor = System.Drawing.Color.Red;
            this.Error_Label.Location = new System.Drawing.Point(43, 277);
            this.Error_Label.Name = "Error_Label";
            this.Error_Label.Size = new System.Drawing.Size(184, 13);
            this.Error_Label.TabIndex = 22;
            this.Error_Label.Text = "Ошибка при обращении к сервису!";
            this.Error_Label.Visible = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 311);
            this.Controls.Add(this.A2_K_Err);
            this.Controls.Add(this.A2_F_Err);
            this.Controls.Add(this.A1_K_Err);
            this.Controls.Add(this.Error_Label);
            this.Controls.Add(this.A1_F_Err);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.Result_F);
            this.Controls.Add(this.Result_K);
            this.Controls.Add(this.Result_S);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.A2_F);
            this.Controls.Add(this.A2_K);
            this.Controls.Add(this.A2_S);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.A1_F);
            this.Controls.Add(this.A1_K);
            this.Controls.Add(this.A1_S);
            this.Controls.Add(this.clear);
            this.Controls.Add(this.Send);
            this.Name = "Form1";
            this.Text = "No Proxy";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Send;
        private System.Windows.Forms.TextBox A1_S;
        private System.Windows.Forms.TextBox A1_K;
        private System.Windows.Forms.TextBox A1_F;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox A2_F;
        private System.Windows.Forms.TextBox A2_K;
        private System.Windows.Forms.TextBox A2_S;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox Result_F;
        private System.Windows.Forms.TextBox Result_K;
        private System.Windows.Forms.TextBox Result_S;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label A1_F_Err;
        private System.Windows.Forms.Label A1_K_Err;
        private System.Windows.Forms.Label A2_K_Err;
        private System.Windows.Forms.Label A2_F_Err;
        private System.Windows.Forms.Button clear;
        private System.Windows.Forms.Label Error_Label;
    }
}

