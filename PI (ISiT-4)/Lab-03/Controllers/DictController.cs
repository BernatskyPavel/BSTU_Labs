using Lab_03.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_03.Controllers
{
    public class DictController : Controller
    {
        private static DictContext context = new DictContext();
        // GET: Dict
        [HttpGet]
        public ActionResult Index()
        {
            context.Records.Sort((x, y) => x.LastName.CompareTo(y.LastName));
            return View(context.Records);
        }

        [HttpGet]
        public ActionResult Add()
        {
            return View();
        }

        [HttpPost]
        public ActionResult AddSave(Record record)
        {
            context.Records.Add(record);
            return RedirectToAction("Index");
        }
       
        [HttpGet]
        public ActionResult Update(Guid? id)
        {
            if(!id.HasValue)
            {
                return RedirectToAction("Index");
            }
            return View(context.Records.Where(r => r.Id == id.Value).FirstOrDefault());
        }

        [HttpPost]
        public ActionResult UpdateSave(Guid? id, Record record)
        {
            if (id.HasValue)
            {
                _ = context.Records.RemoveAll(r => r.Id == id.Value);
                record.Id = id.Value;
                context.Records.Add(record);
            }
            return RedirectToAction("Index");
        }


        public ActionResult Delete(Guid? id)
        {
            if (!id.HasValue)
            {
                return RedirectToAction("Index");
            }
            return View(context.Records.Where(r => r.Id == id.Value).FirstOrDefault());
        }

        [HttpPost]
        public ActionResult DeleteSave(Guid? id)
        {
            if (id.HasValue)
            {
                _ = context.Records.RemoveAll(r => r.Id == id.Value);
            }
            return RedirectToAction("Index");
        }

    }
}