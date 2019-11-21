namespace UserControls
{
    partial class MethodChart
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.GB_statistics = new System.Windows.Forms.GroupBox();
            this.LB_Var = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.LB_Median = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.LB_Mode = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.LB_Mean = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.CH_histogram = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.GB_statistics.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CH_histogram)).BeginInit();
            this.SuspendLayout();
            // 
            // GB_statistics
            // 
            this.GB_statistics.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.GB_statistics.Controls.Add(this.LB_Var);
            this.GB_statistics.Controls.Add(this.label9);
            this.GB_statistics.Controls.Add(this.LB_Median);
            this.GB_statistics.Controls.Add(this.label7);
            this.GB_statistics.Controls.Add(this.LB_Mode);
            this.GB_statistics.Controls.Add(this.label5);
            this.GB_statistics.Controls.Add(this.LB_Mean);
            this.GB_statistics.Controls.Add(this.label2);
            this.GB_statistics.Location = new System.Drawing.Point(736, 3);
            this.GB_statistics.Name = "GB_statistics";
            this.GB_statistics.Size = new System.Drawing.Size(131, 85);
            this.GB_statistics.TabIndex = 15;
            this.GB_statistics.TabStop = false;
            this.GB_statistics.Text = "Estatísticas";
            // 
            // LB_Var
            // 
            this.LB_Var.AutoSize = true;
            this.LB_Var.Location = new System.Drawing.Point(60, 62);
            this.LB_Var.Name = "LB_Var";
            this.LB_Var.Size = new System.Drawing.Size(29, 13);
            this.LB_Var.TabIndex = 7;
            this.LB_Var.Text = "varX";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 62);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(57, 13);
            this.label9.TabIndex = 6;
            this.label9.Text = "Variância: ";
            // 
            // LB_Median
            // 
            this.LB_Median.AutoSize = true;
            this.LB_Median.Location = new System.Drawing.Point(60, 46);
            this.LB_Median.Name = "LB_Median";
            this.LB_Median.Size = new System.Drawing.Size(48, 13);
            this.LB_Median.TabIndex = 5;
            this.LB_Median.Text = "medianX";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 46);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(54, 13);
            this.label7.TabIndex = 4;
            this.label7.Text = "Mediana: ";
            // 
            // LB_Mode
            // 
            this.LB_Mode.AutoSize = true;
            this.LB_Mode.Location = new System.Drawing.Point(60, 30);
            this.LB_Mode.Name = "LB_Mode";
            this.LB_Mode.Size = new System.Drawing.Size(40, 13);
            this.LB_Mode.TabIndex = 3;
            this.LB_Mode.Text = "modeX";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 30);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "Moda: ";
            // 
            // LB_Mean
            // 
            this.LB_Mean.AutoSize = true;
            this.LB_Mean.Location = new System.Drawing.Point(59, 15);
            this.LB_Mean.Name = "LB_Mean";
            this.LB_Mean.Size = new System.Drawing.Size(40, 13);
            this.LB_Mean.TabIndex = 1;
            this.LB_Mean.Text = "meanX";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(5, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Média: ";
            // 
            // CH_histogram
            // 
            this.CH_histogram.BorderlineColor = System.Drawing.Color.Transparent;
            chartArea1.AxisX.MajorGrid.Enabled = false;
            chartArea1.AxisY.MajorGrid.Enabled = false;
            chartArea1.Name = "ChartArea1";
            this.CH_histogram.ChartAreas.Add(chartArea1);
            this.CH_histogram.Dock = System.Windows.Forms.DockStyle.Fill;
            legend1.Name = "Legend1";
            this.CH_histogram.Legends.Add(legend1);
            this.CH_histogram.Location = new System.Drawing.Point(0, 0);
            this.CH_histogram.Name = "CH_histogram";
            this.CH_histogram.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Grayscale;
            series1.BackGradientStyle = System.Windows.Forms.DataVisualization.Charting.GradientStyle.TopBottom;
            series1.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Area;
            series1.IsVisibleInLegend = false;
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            series1.ShadowColor = System.Drawing.Color.Red;
            this.CH_histogram.Series.Add(series1);
            this.CH_histogram.Size = new System.Drawing.Size(893, 201);
            this.CH_histogram.TabIndex = 14;
            this.CH_histogram.Text = "chart1";
            // 
            // MethodChart
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.GB_statistics);
            this.Controls.Add(this.CH_histogram);
            this.Name = "MethodChart";
            this.Size = new System.Drawing.Size(893, 201);
            this.GB_statistics.ResumeLayout(false);
            this.GB_statistics.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CH_histogram)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label2;
        public System.Windows.Forms.Label LB_Var;
        public System.Windows.Forms.Label LB_Median;
        public System.Windows.Forms.Label LB_Mode;
        public System.Windows.Forms.Label LB_Mean;
        public System.Windows.Forms.DataVisualization.Charting.Chart CH_histogram;
        public System.Windows.Forms.GroupBox GB_statistics;
    }
}
