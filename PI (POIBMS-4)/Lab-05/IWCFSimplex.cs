using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Lab_05 {
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface IWCFSimplex {

        [OperationContract]
        int Add(int x, int y);

        [OperationContract]
        string Concat(string s, double d);

        [OperationContract]
        A Sum(A a1, A a2);
    }

    // Use a data contract as illustrated in the sample below to add composite types to service operations.
    // You can add XSD files into the project. After building the project, you can directly use the data types defined there, with the namespace "Lab_05.ContractType".
    [DataContract]
    public class A {
        [DataMember]
        public string s;
        [DataMember]
        public int k;
        [DataMember]
        public float f;

        public static A operator +(A lhs, A rhs)
        {
            return new A {
                s = lhs.s + rhs.s,
                k = lhs.k + rhs.k,
                f = lhs.f + rhs.f
            };
        }
    }
}
