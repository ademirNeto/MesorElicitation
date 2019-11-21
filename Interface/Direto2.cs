using System;
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
using UserControls;

namespace InterfaceUnificada
{
    public partial class Direto2 : MainEngineClass
    {
        private List<NumericUpDownButton> numericUpDownList;
        public TabPage tabPageDireto;//, tp;
        int k, l = 0, numberInterval;//,iteracao= 2
        public string resposta;
        double[] W;
        double intervalSize, timeConsuption; //min, max,
        public double sumNormalize;
        ArrayList backupCredibilities;
        double[] doubleX;
        double[] doublefx;
        String[] label_texts;

        public Direto2(ElicitationParameters p, IFormPrincipal ifPrincipal) {
            InitializeComponent();
            this.ifPrincipal = ifPrincipal;
            this.question = this.ifPrincipal.getQuestion();
            this.p = p.getClone();

            this.p.max = p.max;
            this.p.min = p.min;
            this.upperOfLowerInterval = p.upperOfLowerInterval;
            this.lowerOfUpperInterval = p.lowerOfUpperInterval;
            this.p.center = p.center;
            this.p.cred = p.cred;
            this.p.index = p.index;
            this.p.iteracao = p.iteracao + 1;
            this.times = p.times;
            this.answers = p.answers;
            this.statistics = p.statistics;
            this.W = p.W;
            this.x = p.x;
            this.k = p.k;
            this.numberInterval = k;
            this.intervalSize = (p.min + p.max) / p.k;

            initMethod2();
            this.loadConfigMethodForVariable();
            
            this.configChartSeriesDirect(p.min, p.max, p.k);
        }
        
        private void updateHistogram()
        {

        }

        public void initMethod2()
        {
            int nPoints = 2 * this.k-2;
            this.y = new double[nPoints];

            this.Fx = ElicitationHelper.getCumulative(this.W);//cumulatives

            label_texts = new String[this.numberInterval];
            this.setQuestionAlternatives ();
            for(int i = 0; i < this.numberInterval; i++) {
                label_texts[i] = ((Alternative)this.question.alternatives[i]).evento;
            }
            this.lista = ElicitationHelper.buildStatistics(this.x, Fx, this.numberInterval, this.p.min, this.p.max);

            configInputControls2(label_texts);

            this.InitializeComponent_DistributionResults(this.lista);
        }

        public void configInputControls2(string[] lb_texts)
        {
            int DistanceX = 140;
            NUDL_options.Distance = DistanceX;
            NUDL_options.NumberControls = this.numberInterval;
            NUDL_options.LbTextList = lb_texts;
        }

        override protected IMethod updateMethod()
        {
            try
            {
                double[] creds = getCredibilities ();
                this.W = new double[this.numberInterval+1];
                creds.CopyTo (this.W, 1);
                this.Fx = ElicitationHelper.getCumulative(this.W);

                this.times.Add(timeConsuption / 1000);  //Armazenar nas listas os valores do tempo consumido e das respostas
                this.InitializeComponent_DistributionResults(ElicitationHelper.buildStatistics(this.x, this.Fx, this.numberInterval, this.p.min, this.p.max));
            } catch(Exception exc) {
                ifPrincipal.DisplayMessage (exc.StackTrace, true);
            }
            return null;
        }

        override public double[] getCredibilities()
        {
            return ElicitationHelper.updateCredibilitiesDirectMethod(NUDL_options.getProbabilities());
        }

        protected void OnMouseUpNumericUpDown(object sender, MouseEventArgs e)
        {
            updateMethod();
        }

        protected void OnKeyUpNumericUpDown(object sender, KeyEventArgs e)
        {
            updateMethod();
        }

        private double[,] labelsDiretoToArrayDouble(String[] st_array) {
            double[,] list = new double[st_array.Length, 2];
            int i, j;

            for(i = j = 0; i < st_array.Length; i++) {
                string[] split = st_array[i].Replace('[', ' ').Replace(']', ' ').Replace(')', ' ').Trim().Split(new char[] { ';' });
                double outdouble1, outdouble2;
                if(double.TryParse(split[0], out outdouble1) && double.TryParse(split[1], out outdouble2)) {
                    list[i, 0] = outdouble1;
                    list[i, 1] = outdouble2;
                    j++;
                }
            }
            return list;
        }

        public double getCorrectBin(string parameter) {
            string st_correctAnswer = this.question.respostaCerta;
            double correctAnswer = -1;
            if(st_correctAnswer.Equals(DefaultConfig.ST_DIST_NULL)) {
                st_correctAnswer = ifPrincipal.getCB_resultadoExperimento().Text;
            }
            correctAnswer = Double.Parse(st_correctAnswer);
            int correctBin = -2;//bin_0 = [x_0, x_1], ...

            double[,] intervals = labelsDiretoToArrayDouble(label_texts);

            //int m = this.x.Length - 1;
            //if()
            if(intervals[0, 0] > correctAnswer)
                correctBin = -2;
            else
                correctBin = -1;

            int m = (intervals.Length/2);
            for(int i = 0; i < m; i++) {
                if((intervals[i,0] <= correctAnswer && intervals[i,1] > correctAnswer )) {
                    correctBin = i;
                }
            }

            return correctBin;
        }
        
        override public bool getFinishedMethod() {
            try {
                NUDL_options.updateProbabilities();
                return true;

            } catch (Exception e) {
                throw e;
            }
        }
    }
}