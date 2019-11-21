using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace InterfaceUnificada {
    public class ElicitationManager: IMethodManager {

        IFormPrincipal ifPrincipal;
        ElicitationMethod elicitationMethod;
        IMethod currentMethod;
        public List<MainEngineClass> MethodNode = new List<MainEngineClass>(0);
        List<IPanelMethod> firstPanelList = new List<IPanelMethod>();

        public ElicitationManager(ElicitationMethod elicitationMethod, IFormPrincipal ifPrincipal) {
            this.ifPrincipal = ifPrincipal;
            this.elicitationMethod = elicitationMethod;
            firstPanelList.Add(new FirstElicitationPanel());

        }

        public void addNewReference(IMethod method) {
            throw new NotImplementedException();
        }

        public Control getFirstPanel() {
            if(elicitationMethod == ElicitationMethod.Firmino || elicitationMethod == ElicitationMethod.Direto || elicitationMethod == ElicitationMethod.Bissecao) {
                return firstPanelList[0].getPanel();
            } else {
                return null;
            }
        }

        public void sendRerefence(IMethodManager iMethManager) {
            throw new NotImplementedException();
        }


        public IMethod removeLastReference() {
            throw new NotImplementedException();
        }



        public IMethod getCurrentMethod() {
            return currentMethod;
        }


        public IMethod getMethodBeforeCurrent() {
            throw new NotImplementedException();
        }
    }
}
