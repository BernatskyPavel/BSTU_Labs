using Simple.OData.Client;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Syndication;
using System.ServiceModel.Web;
using System.Text;

namespace Lab_07
{
    public class NotesFeed : INotesFeed
    {
        private ODataClient client = new ODataClient(new Uri("http://localhost:789/PI-POIBMS-4/Lab-06/WCFDataSimplex.svc/"));

        public SyndicationFeedFormatter GetNotes()
        {
            try
            {
                var task = client.GetMetadataAsync();
                task.Wait();
            }
            catch (Exception e)
            {
                WebOperationContext.Current.OutgoingResponse.StatusCode= System.Net.HttpStatusCode.ServiceUnavailable;
                WebOperationContext.Current.OutgoingResponse.StatusDescription = "Data Service unavailable";
                using(var file = File.CreateText("E:/syn-log.txt")){
                    file.WriteLine(e.InnerException.Message);
                }
                return null;
            }

            string s_id = WebOperationContext.Current.IncomingRequest.UriTemplateMatch.QueryParameters["id"];
            int id = 0;
            SyndicationFeed feed = null;
            List<SyndicationItem> items = new List<SyndicationItem>();
            if (!int.TryParse(s_id, out id))
            {
                feed = new SyndicationFeed("Students List", "A students available for subscription.", null);
                System.Threading.Tasks.Task<IEnumerable<PII6Model.Students>> task = client.For<PII6Model.Students>().FindEntriesAsync();
                task.Wait();
                foreach (PII6Model.Students student in task.Result)
                {
                    SyndicationItem item = new SyndicationItem($"Student №{student.Id}", student.Name, null);
                    items.Add(item);
                }
            }
            else
            {
                try
                {
                    System.Threading.Tasks.Task<PII6Model.Students> task = client.For<PII6Model.Students>().Key(id).FindEntryAsync();
                    task.Wait();
                    feed = new SyndicationFeed($"Student №{id} notes", $"Notes of student: {task.Result.Name}.", null);
                    System.Threading.Tasks.Task<IEnumerable<PII6Model.Notes>> notes_task = client.For<PII6Model.Notes>().Filter(n => n.Id == id).FindEntriesAsync();
                    task.Wait();
                    foreach (PII6Model.Notes note in notes_task.Result)
                    {
                        SyndicationItem item = new SyndicationItem($"Note in {note.Subj}", note.Note.ToString(), null);
                        items.Add(item);
                    }
                }
                catch (Exception e)
                {
                    WebOperationContext.Current.OutgoingResponse.SetStatusAsNotFound();
                    using (var file = File.CreateText("E:/syn-log2.txt"))
                    {
                        file.WriteLine(e.InnerException.Message);
                    }
                    return null;
                }
            }  
            
            feed.Items = items;
            string query = WebOperationContext.Current.IncomingRequest.UriTemplateMatch.QueryParameters["format"];
            SyndicationFeedFormatter formatter = null;
            if (query == "atom")
            {
                formatter = new Atom10FeedFormatter(feed);
            }
            else
            {
                formatter = new Rss20FeedFormatter(feed);
            }

            return formatter;
        }
    }
}
