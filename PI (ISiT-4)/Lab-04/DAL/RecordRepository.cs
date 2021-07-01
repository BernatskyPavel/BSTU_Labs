using Lab_04.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Lab_04.DAL
{
    public class RecordRepository : IRecordRepository, IDisposable
    {
        private DictContext _dictContext;
        private bool isDisposed = false;

        public RecordRepository(DictContext dictContext)
        {
            this._dictContext = dictContext;
        }

        public void DeleteRecord(Guid recordId)
        {
            Record record = this._dictContext.Records.Find(recordId);
            this._dictContext.Records.Remove(record);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        public Record GetRecordByID(Guid recordId)
        {
            return this._dictContext.Records.Find(recordId);
        }

        public IEnumerable<Record> GetRecords()
        {
            return this._dictContext.Records.ToList();
        }

        public void InsertRecord(Record record)
        {
            this._dictContext.Records.Add(record);
        }

        public void Save()
        {
            this._dictContext.SaveChanges();
        }

        public void UpdateRecord(Record record)
        {
            this._dictContext.Entry(record).State = EntityState.Modified;
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!isDisposed)
            {
                if (disposing)
                {
                    this._dictContext.Dispose();
                }
            }
            this.isDisposed = true;
        }
    }
}