using Lab_04.DAL;
using Lab_04.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_04.Controllers
{
    public class DictController : Controller
    {
        private IRecordRepository records;
        // GET: Dict

        public DictController()
        {
            this.records = new RecordRepository(new DictContext());
        }
        public DictController(IRecordRepository records)
        {
            this.records = records;
        }


        [HttpGet]
        public ActionResult Index()
        {
            return View(records.GetRecords().OrderBy(x => x.Lastname).ToList());
        }

        [HttpGet]
        public ActionResult Add()
        {
            return View();
        }

        [HttpPost]
        public ActionResult AddSave(Record record)
        {
            records.InsertRecord(record);
            records.Save();
            return RedirectToAction("Index");
        }
       
        [HttpGet]
        public ActionResult Update(Guid? id)
        {
            if(!id.HasValue)
            {
                return RedirectToAction("Index");
            }
            return View(records.GetRecordByID(id.Value));
        }

        [HttpPost]
        public ActionResult UpdateSave(Guid? id, Record record)
        {
            if (id.HasValue)
            {
                records.UpdateRecord(record);
                records.Save();
            }
            return RedirectToAction("Index");
        }


        public ActionResult Delete(Guid? id)
        {
            if (!id.HasValue)
            {
                return RedirectToAction("Index");
            }
            return View(records.GetRecordByID(id.Value));
        }

        [HttpPost]
        public ActionResult DeleteSave(Guid? id)
        {
            if (id.HasValue)
            {
                records.DeleteRecord(id.Value);
                records.Save();
            }
            return RedirectToAction("Index");
        }

    }
}