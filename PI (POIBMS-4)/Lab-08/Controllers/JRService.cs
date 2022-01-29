using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.SessionState;

namespace Lab_08.Controllers {
    public class JRService {
        HttpSessionState store = null;
        public static readonly string _exit = "error_exit";
        public JRService(HttpSessionState store) {
            this.store = store;
        }
        public int SetM(string k, int x) {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            this.store.Add(k, x);
            return x;
        }
        public int GetM(string k) {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            object obj = this.store[k];
            return Convert.ToInt32(obj);
        }

        public int AddM(string k, int x) {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            int sum = unchecked(Convert.ToInt32(this.store[k]) + x);
            this.store[k] = sum;
            return sum;
        }

        public int SubM(string k, int x) {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            int sub = unchecked(Convert.ToInt32(this.store[k]) - x);
            this.store[k] = sub;
            return sub;
        }

        public int MulM(string k, int x) {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            int mul = unchecked(Convert.ToInt32(this.store[k]) * x);
            this.store[k] = mul;
            return mul;
        }

        public int DivM(string k, int x) {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            int div = unchecked(Convert.ToInt32(this.store[k]) / x);
            this.store[k] = div;
            return div;
        }

        public string ErrorExit() {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            this.store.Clear();
            this.store[_exit] = true;
            return "Successfully exited.";
        }
            
        public string Reload() {
            if (this.store == null) {
                throw new ArgumentNullException("store");
            }
            this.store.Clear();
            return "Successfully reloaded.";
        }
    }
}