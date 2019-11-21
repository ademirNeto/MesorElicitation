using System;//teste5
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using MySql.Data;
using MySql.Data.MySqlClient;
using System.Diagnostics;
using CalibrationEngine;

namespace InterfaceUnificada {
    public partial class Bisection : MainEngineClass {
        private Variable variable;
        private List<double> intervals;
        private double middlePoint;

        public Bisection(ElicitationParameters p, IFormPrincipal ifPrincipal): base() {
            InitializeComponent();
            this.ifPrincipal = ifPrincipal;
            this.question = this.ifPrincipal.getQuestion();
            this.p = p.getClone();

            //this.upperOfLowerInterval = p.upperOfLowerInterval;
            //this.lowerOfUpperInterval = p.lowerOfUpperInterval;
            this.lowerOfUpperInterval = new List<double> ();
            this.upperOfLowerInterval = new List<double> ();
            //this.center = p.center;
            this.p.cred = p.cred;
            this.p.index = p.index;
            this.p.iteracao = p.iteracao + 1;
            this.times = p.times;
            this.answers = p.answers;
            this.statistics = p.statistics;
            this.x = p.x;
            
            if (ifPrincipal.isTrainingPhase()) {//Permitir apenas uma iteração caso seja treinamento.
                //List<double> lines = new List<double>();
                //this.ifPrincipal.markChoosableAreaChartSeries(lines);
                if (this.p.iteracao > 1) {
                    this.RB_semPreferencia.Enabled = false;
                    this.TR_mdSearch.Enabled = false;
                }
            } else {
                if (this.p.iteracao >= 4) {
                    this.RB_semPreferencia.Enabled = false;
                    this.TR_mdSearch.Enabled = false;
                }
            }

            this.intervals = this.x.ToList();

            showMainPanel(p.min, p.center, p.max, this.p.cred, this.p.index);
            this.loadConfigMethodForVariable();

            List<double> lines = new List<double>();
            lines.Add(this.p.min);
            lines.Add(this.p.center);
            lines.Add(this.p.max);
            this.ifPrincipal.markChoosableAreaChartSeries(lines);
            
        }

        //Construtor
        public void showMainPanel(double min, double center, double max, double cred, int index) {
            string q2 = Engine.EngineInterface.getNextBinaryQuestion(min, center, max, cred, index, Engine.EngineInterface.BISECTION);

            if (index > -1) {
                this.intervals.Add(center);
            }
            this.intervals.Sort();
            this.x = this.intervals.ToArray();

            this.lista = q2.Split(new char[] { ';' });
            this.p.min = Engine.EngineInterface.nextLower;
            this.p.max = Engine.EngineInterface.nextUpper;
            this.upperOfLowerInterval.Add(this.p.max);
            this.lowerOfUpperInterval.Add(this.p.min);
            this.p.center = (this.p.min + this.p.max) / 2.0;

            int length = this.lista.Length;
            this.LB_condition.Text = lista[length - 4];
            this.LB_intermediate.Text = lista[length - 3];
            //this.TB_Question.Text = varName;
            TreeNode Root = this.TR_mdSearch.Nodes[0];
            Root.Text = "[" + this.p.min + ", " + this.p.max + "]";
            TreeNodeCollection Children = Root.Nodes;
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint1 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(1D, this.p.min + ", " + this.p.max);
            dataPoint1.Label = "Intervalo Inferior";
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint2 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(2D, this.p.min + ", " + this.p.max);
            dataPoint2.Label = "Intervalo Superior";
            FG_buscaMediana.Series["Decisão"].Points[0] = dataPoint1;
            FG_buscaMediana.Series["Decisão"].Points[1] = dataPoint2;

            Children[0].Text = lista[length - 2];
            Children[1].Text = lista[length - 1];
            this.InitializeComponent_DistributionResults(this.lista);

            
        }

        private void RB_semPreferencia_Click(object sender, EventArgs e) {
            try {
                this.BT_Update_Click(sender, e);
            } catch (Exception) {
                MessageBox.Show("Problema de execução! Clique no botão back para eduzir novamente o quantil atual.");
            }

            

        }

        private void BT_Back_Click(object sender, EventArgs e) {
            this.BT_back_ClickAction(sender, e);
        }

        private void createNewChildren (TreeNode node) {
            this.p.center = (this.upperOfLowerInterval[node.Level] + this.lowerOfUpperInterval[node.Level]) / 2.0;
            TreeNode newCh0 = new TreeNode ("[" + this.p.min + ", " + this.p.center + ") ou entre");
            TreeNode newCh1 = new TreeNode ("[" + this.p.center + ", " + this.p.max + "]?");
            node.Nodes.Add (newCh0);
            node.Nodes.Add (newCh1);
            node.Expand ();
        }

        private void uncheckRamification (TreeNode node) {
            TreeNodeCollection children = node.Nodes;
            for(int i=0; i<children.Count; i++){
                uncheckRamification (children[i]);
            }
            if(node.Checked == true) {
                node.Checked = false;
                node.Nodes.Clear ();
                if(this.RB_semPreferencia.Checked) {
                    this.RB_semPreferencia.Checked = false;
                    try {
                        Engine.EngineInterface.deleteChildren (this.p.min, this.p.center, this.p.max);
                    } catch(Exception ev) {
                        MessageBox.Show (ev.Message+"-----------\n"+ev.StackTrace);
                    }
                }
            }
        }

        private void TR_mdSearch_AfterCheck (object sender, TreeViewEventArgs e) {
            TreeNode ch = e.Node;
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint = null;
            int index = 0;
            TreeNode parent = ch.Parent;
            double[] interval = new double[2]; 
            if(parent!=null){
                if(ch.Checked) {
                    interval = getIntervals (e.Node.Text);
                    //working on eventual decision changing actions
                    TreeNode brother = parent.Nodes[1 - ch.Index];
                    if(brother.Checked)
                        brother.Checked=false;
                    //updating bounds
                    if(ch.Index == 0) {
                        this.upperOfLowerInterval.Add (this.p.center);
                        this.lowerOfUpperInterval.Add (this.lowerOfUpperInterval[this.lowerOfUpperInterval.Count-1]);
                        dataPoint = new System.Windows.Forms.DataVisualization.Charting.DataPoint (1D, this.p.min + "," + this.p.center);
                        dataPoint.Label = "Intervalo Inferior";
                    } else {
                        this.lowerOfUpperInterval.Add(this.p.center);
                        this.upperOfLowerInterval.Add (this.upperOfLowerInterval[this.upperOfLowerInterval.Count-1]);
                        dataPoint = new System.Windows.Forms.DataVisualization.Charting.DataPoint (2D, this.p.center + "," + this.p.max);
                        dataPoint.Label = "Intervalo Superior";
                        index = 1;
                    }
                    //creating new children
                    createNewChildren (ch);                    
                } else {
                    interval = getIntervals (parent.Text);
                    TreeNodeCollection ch_children = ch.Nodes;
                    for(int i=0; i<ch_children.Count; i++) {
                        uncheckRamification (ch_children[i]);
                    }
                    ch.Nodes.Clear ();
                    //string[] list = parent.Text.Split(new char[] { ',' });
                    //string[] aux;
                    if(ch.Index == 0) {
                        //aux = list[1].Split(new char[] { ']',')' });
                        //this.upperOfLowerInterval = Convert.ToDouble(aux[0]);//TODO: exception ao converter  "0.5) ou entre" para inteiro.
                        dataPoint = new System.Windows.Forms.DataVisualization.Charting.DataPoint(1D, this.p.min + "," + this.upperOfLowerInterval[parent.Level]);
                        dataPoint.Label = "Intervalo Inferior";
                    } else {
                        //aux = list[0].Split(new char[] { '[' });
                        //this.lowerOfUpperInterval = Convert.ToDouble(aux[1]);
                        dataPoint = new System.Windows.Forms.DataVisualization.Charting.DataPoint (2D, this.lowerOfUpperInterval[parent.Level] + "," + this.p.max);
                        dataPoint.Label = "Intervalo Superior";
                        index = 1;
                    }
                    this.p.center = (this.upperOfLowerInterval[parent.Level] + this.lowerOfUpperInterval[parent.Level]) / 2.0;
                    this.upperOfLowerInterval.RemoveAt (ch.Level);
                    this.lowerOfUpperInterval.RemoveAt (ch.Level);
                }
            }else{
                interval[0] = this.p.rootMin;
                interval[1]= this.p.rootMax;
            }
            if(dataPoint != null)
                FG_buscaMediana.Series["Decisão"].Points[index] = dataPoint;

            markChoosableAreaChartSeries(this.p.min, this.p.center, this.p.max);    
            
        }

        private void BT_Finalizar_Click(object sender, EventArgs e) {
            this.FinishMethod();
        }

        override public int getElicitationMethod() {
            return CalibrationInterface.MethodType.BISECTION;
        }

        override protected IMethod updateMethod() {
            ElicitationParameters par = p.getClone();
            try {

                par.cred = 0.5;
                string resposta = this.p.center + "";
                par.answers = this.answers;
                par.answers.Add(resposta);
                par.x = (Double[])this.x.Clone();
                
                par.times = this.times;

                this.statistics.Add(Convert.ToDouble(lista[lista.Length - 8]));
                this.statistics.Add(Convert.ToDouble(lista[lista.Length - 7]));
                this.statistics.Add(Convert.ToDouble(lista[lista.Length - 6]));
                this.statistics.Add(Convert.ToDouble(lista[lista.Length - 5]));
                par.statistics = statistics;
                par.min = this.p.min;
                par.center = this.p.center;
                par.max = this.p.max;
                par.iteracao = this.p.iteracao;
                par.index++;

                Bisection bisection = new Bisection(par, this.ifPrincipal);

                return bisection;
            } catch(Exception ex) {
                throw;
            }
        }

        public override void BT_back_ClickAction(object sender, EventArgs e) {
            base.BT_back_ClickAction(sender, e);
            try{
                Engine.EngineInterface.deleteChildren(this.p.min, this.p.center, this.p.max);
            } catch (Exception exc) {
                MessageBox.Show(exc.Message + "-----------\n" + exc.StackTrace);
            }
            
            IMethod method = methodManager.getCurrentMethod();

            if(method != null){
                Bisection b = (Bisection)method;
                b.RB_semPreferencia.Checked = false;
                if (ifPrincipal.isTrainingPhase() == false) {
                    ((Bisection)method).markChoosableAreaChartSeries(((Bisection)method).p.min, ((Bisection)method).middlePoint, ((Bisection)method).p.max);    
                }
                
            }
        }

        public int getCorrectBin(string parameter) {
            int correctBin = 0;
            String[] dist = question.distribuicao.Trim().Split(new char[] { ';' });
            double tmp = double.Parse(dist[1]);

            if (x[0] > tmp) {
                correctBin = -2;
            } else if (x[x.Length - 1] < tmp) {
                correctBin = -1;
            } else {
                for (int i = 0; i < x.Length; i++) {
                    if (x[i] <= tmp)
                        correctBin = i;
                }
            }
            return correctBin;
            
        }
    }
}
