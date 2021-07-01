using Lab_04.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_04.DAL
{
    public interface IRecordRepository: IDisposable
    {
        IEnumerable<Record> GetRecords();
        Record GetRecordByID(Guid recordId);
        void InsertRecord(Record record);
        void DeleteRecord(Guid recordId);
        void UpdateRecord(Record record);
        void Save();
    }
}
