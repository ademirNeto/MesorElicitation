using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace InterfaceUnificada {
    public partial class ProcessFinished : Form, IMethod {
        public ProcessFinished() {
            InitializeComponent();
        }

        public bool getFinishedMethod() {
            return true;
        }

        public double[] getCredibilities() {
            throw new NotImplementedException();
        }

        public double getCorrectBin(string parameter) {
            throw new NotImplementedException();
        }

        public int getElicitationMethod() {
            throw new NotImplementedException();
        }

        public bool FinishMethod() {
            throw new NotImplementedException();
        }

        public Control getDecisionPanel() {
            return null;
        }

        public Control getHistogramPanel() {
            return this.panel1;
        }

        public void setQuestionAlternatives() {
            throw new NotImplementedException();
        }

        public void setHistogramStatistics(Statistics statistics) {
            throw new NotImplementedException();
        }

        public double[] getTrueDistribution(Question question) {
            throw new NotImplementedException();
        }

        public void sendRerefence(IMethodManager iMethManager) {
            throw new NotImplementedException();
        }

        public double[] getX() {
            throw new NotImplementedException();
        }

        public void setX(double[] xArray) {
            throw new NotImplementedException();
        }

        public List<double> getGrid() {
            throw new NotImplementedException();
        }


        public ElicitationParameters getStatistics() {
            throw new NotImplementedException();
        }
    }
}
