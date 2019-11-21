namespace InterfaceUnificada
{
    partial class Bisection
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint1 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(1D, "0,10");
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint2 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(2D, "0,10");
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Node00");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Node01");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Node0", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2});
            this.label9 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.RB_semPreferencia = new System.Windows.Forms.RadioButton();
            this.FG_buscaMediana = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.GB_decision = new System.Windows.Forms.GroupBox();
            this.TR_mdSearch = new System.Windows.Forms.TreeView();
            this.LB_intermediate = new System.Windows.Forms.Label();
            this.LB_condition = new System.Windows.Forms.Label();
            this.PN_Decision.SuspendLayout();
            this.PN_Chart.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.FG_buscaMediana)).BeginInit();
            this.GB_decision.SuspendLayout();
            this.SuspendLayout();
            // 
            // PN_Decision
            // 
            this.PN_Decision.Controls.Add(this.LB_condition);
            this.PN_Decision.Controls.Add(this.LB_intermediate);
            this.PN_Decision.Controls.Add(this.GB_decision);
            this.PN_Decision.Size = new System.Drawing.Size(908, 173);
            this.PN_Decision.Controls.SetChildIndex(this.GB_decision, 0);
            this.PN_Decision.Controls.SetChildIndex(this.BT_Update, 0);
            this.PN_Decision.Controls.SetChildIndex(this.LB_intermediate, 0);
            this.PN_Decision.Controls.SetChildIndex(this.BT_back, 0);
            this.PN_Decision.Controls.SetChildIndex(this.LB_condition, 0);
            this.PN_Decision.Controls.SetChildIndex(this.BT_Finish1, 0);
            // 
            // BT_back
            // 
            this.BT_back.Location = new System.Drawing.Point(663, 118);
            // 
            // BT_Update
            // 
            this.BT_Update.Location = new System.Drawing.Point(582, 118);
            this.BT_Update.Visible = false;
            // 
            // BT_Finish1
            // 
            this.BT_Finish1.Location = new System.Drawing.Point(744, 118);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 77);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(57, 13);
            this.label9.TabIndex = 6;
            this.label9.Text = "Variância: ";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 55);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(54, 13);
            this.label7.TabIndex = 4;
            this.label7.Text = "Mediana: ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 34);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "Moda: ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Média: ";
            // 
            // RB_semPreferencia
            // 
            this.RB_semPreferencia.AutoSize = true;
            this.RB_semPreferencia.Location = new System.Drawing.Point(6, 100);
            this.RB_semPreferencia.Name = "RB_semPreferencia";
            this.RB_semPreferencia.Size = new System.Drawing.Size(136, 17);
            this.RB_semPreferencia.TabIndex = 2;
            this.RB_semPreferencia.TabStop = true;
            this.RB_semPreferencia.Text = "Não Tenho Preferência";
            this.RB_semPreferencia.UseVisualStyleBackColor = true;
            //this.RB_semPreferencia.CheckedChanged += new System.EventHandler(this.RB_semPreferencia_Click);
            this.RB_semPreferencia.Click += new System.EventHandler(this.RB_semPreferencia_Click);
            // 
            // FG_buscaMediana
            // 
            this.FG_buscaMediana.BorderlineColor = System.Drawing.Color.Black;
            this.FG_buscaMediana.BorderlineWidth = 5;
            chartArea1.AxisX.MajorGrid.Enabled = false;
            chartArea1.AxisY.MajorGrid.Enabled = false;
            chartArea1.BackColor = System.Drawing.Color.Transparent;
            chartArea1.Name = "ChartArea1";
            this.FG_buscaMediana.ChartAreas.Add(chartArea1);
            this.FG_buscaMediana.Location = new System.Drawing.Point(392, 11);
            this.FG_buscaMediana.Name = "FG_buscaMediana";
            this.FG_buscaMediana.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Excel;
            series1.BorderColor = System.Drawing.Color.Black;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.RangeBar;
            series1.Font = new System.Drawing.Font("Times New Roman", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            series1.IsXValueIndexed = true;
            series1.Name = "Decisão";
            dataPoint1.Label = "Intervalo Inferior";
            dataPoint2.Label = "Intervalo Superior";
            series1.Points.Add(dataPoint1);
            series1.Points.Add(dataPoint2);
            series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            series1.YValuesPerPoint = 2;
            series1.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            this.FG_buscaMediana.Series.Add(series1);
            this.FG_buscaMediana.Size = new System.Drawing.Size(504, 68);
            this.FG_buscaMediana.TabIndex = 10;
            this.FG_buscaMediana.Text = "Decisões";
            // 
            // GB_decision
            // 
            this.GB_decision.Controls.Add(this.FG_buscaMediana);
            this.GB_decision.Controls.Add(this.TR_mdSearch);
            this.GB_decision.Controls.Add(this.RB_semPreferencia);
            this.GB_decision.Location = new System.Drawing.Point(3, 16);
            this.GB_decision.Name = "GB_decision";
            this.GB_decision.Size = new System.Drawing.Size(902, 134);
            this.GB_decision.TabIndex = 0;
            this.GB_decision.TabStop = false;
            this.GB_decision.Text = "Decisão";
            // 
            // TR_mdSearch
            // 
            this.TR_mdSearch.BackColor = System.Drawing.Color.White;
            this.TR_mdSearch.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.TR_mdSearch.CheckBoxes = true;
            this.TR_mdSearch.LineColor = System.Drawing.Color.DarkRed;
            this.TR_mdSearch.Location = new System.Drawing.Point(6, 12);
            this.TR_mdSearch.Name = "TR_mdSearch";
            treeNode1.Name = "Node00";
            treeNode1.Text = "Node00";
            treeNode2.Name = "Node01";
            treeNode2.Text = "Node01";
            treeNode3.Checked = true;
            treeNode3.Name = "Node0";
            treeNode3.Text = "Node0";
            this.TR_mdSearch.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode3});
            this.TR_mdSearch.Size = new System.Drawing.Size(370, 82);
            this.TR_mdSearch.TabIndex = 0;
            this.TR_mdSearch.AfterCheck += new System.Windows.Forms.TreeViewEventHandler(this.TR_mdSearch_AfterCheck);
            // 
            // LB_intermediate
            // 
            this.LB_intermediate.AutoSize = true;
            this.LB_intermediate.Location = new System.Drawing.Point(57, 0);
            this.LB_intermediate.Name = "LB_intermediate";
            this.LB_intermediate.Size = new System.Drawing.Size(86, 13);
            this.LB_intermediate.TabIndex = 12;
            this.LB_intermediate.Text = "IntermediateText";
            // 
            // LB_condition
            // 
            this.LB_condition.AutoSize = true;
            this.LB_condition.BackColor = System.Drawing.Color.White;
            this.LB_condition.Location = new System.Drawing.Point(0, 0);
            this.LB_condition.Name = "LB_condition";
            this.LB_condition.Size = new System.Drawing.Size(51, 13);
            this.LB_condition.TabIndex = 11;
            this.LB_condition.Text = "Condition";
            // 
            // Bisection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(948, 595);
            this.Name = "Bisection";
            this.Text = "Bisection";
            this.PN_Decision.ResumeLayout(false);
            this.PN_Decision.PerformLayout();
            this.PN_Chart.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.FG_buscaMediana)).EndInit();
            this.GB_decision.ResumeLayout(false);
            this.GB_decision.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        //private System.Windows.Forms.GroupBox groupBox2;
        //private System.Windows.Forms.Label // LB_Var;
        //private System.Windows.Forms.Label // LB_Median;
        //private System.Windows.Forms.Label // LB_Mode;
        //private System.Windows.Forms.Label //LB_Mean;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label LB_condition;
        private System.Windows.Forms.Label LB_intermediate;
        private System.Windows.Forms.GroupBox GB_decision;
        private System.Windows.Forms.DataVisualization.Charting.Chart FG_buscaMediana;
        private System.Windows.Forms.TreeView TR_mdSearch;
        private System.Windows.Forms.RadioButton RB_semPreferencia;
    }
}