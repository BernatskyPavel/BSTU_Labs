using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebClients.Services.Lab_04 {
    public class Simplex : ISimplexSoap {
        public int Add(int x, int y)
        {
            return x + y;
        }

        public int AddS(int a, int b)
        {
            throw new NotImplementedException();
        }

        public string Concat(string s, double d)
        {
            return $"{s}{d}";
        }

        public A Sum(A a1, A a2)
        {
            return new A {
                S = a1.S + a2.S,
                K = a1.K + a2.K,
                F = a1.F + a2.F,
            };
        }
    }
}