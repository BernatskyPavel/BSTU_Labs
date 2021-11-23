using PII6Model;
using Simple.OData.Client;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data.Services.Client;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Lab_06_v3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ObservableCollection<Students> students = new ObservableCollection<Students>();
        private ObservableCollection<Notes> current_notes = new ObservableCollection<Notes>();
        private Students current_student = null;
        private ODataClient client = null;
        private bool is_adding = false;
        private bool is_adding_note = false;
        private bool _handle = true;
        private bool _handle_note = true;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void RefreshNoteList()
        {
            this.notesList.ItemsSource = null;
            this.notesList.ItemsSource = this.current_notes;
        }

        private void RefreshStudentList()
        {
            this.studentList.ItemsSource = null;
            this.studentList.ItemsSource = this.students;
        }

        private int GetMaxNoteId()
        {
            Task<Notes> task = client.For<Notes>().OrderByDescending(x => x.NoteId).Top(1).FindEntryAsync();
            task.Wait();
            return task.Result != null ? task.Result.NoteId : 0;
        }

        private int GetMaxStudentId()
        {
            Task<Students> task = client.For<Students>().OrderByDescending(x => x.Id).Top(1).FindEntryAsync();
            task.Wait();
            return task.Result != null ? task.Result.Id : 0;
        }

        private void grid_AddingNewItem(object sender, AddingNewItemEventArgs e)
        {
            if (sender is DataGrid)
            {
                switch ((sender as DataGrid).Name)
                {
                    case "studentList":
                        is_adding = e.NewItem == null && !is_adding;
                        break;
                    case "notesList":
                        is_adding_note = e.NewItem == null && !is_adding_note;
                        break;
                    default: break;
                }

            }
        }


        private void PreviewKeyDownHandler(object sender, KeyEventArgs e)
        {
            if (sender is DataGrid)
            {
                if (Key.Delete == e.Key)
                {
                    var grid = (DataGrid)sender;
                    switch (grid.Name)
                    {
                        case "studentList":
                            foreach (object row in grid.SelectedItems)
                            {
                                if (row.ToString() != "{NewItemPlaceholder}")
                                {
                                    var task = client.For<Students>().Key((row as Students).Id).DeleteEntryAsync();
                                    task.Wait();
                                }
                            }
                            break;
                        case "notesList":
                            foreach (object row in grid.SelectedItems)
                            {
                                if (row.ToString() != "{NewItemPlaceholder}")
                                {
                                    var task = client.For<Notes>().Key((row as Notes).NoteId).DeleteEntryAsync();
                                    task.Wait();
                                }
                            }
                            break;
                        default: break;
                    }

                }
            }
        }

        private void studentList_RowEditEnding(object sender, DataGridRowEditEndingEventArgs e)
        {

            if (is_adding)
            {
                if (_handle && e.EditAction == DataGridEditAction.Commit)
                {
                    _handle = false;
                    studentList.CommitEdit();
                    var task = client
                        .For<Students>()
                        .Set(new Students { Id = GetMaxStudentId() + 1, Name = (e.Row.Item as Students).Name ?? String.Empty })
                        .InsertEntryAsync();
                    task.Wait();
                    Students result = task.Result;
                    (e.Row.Item as Students).Id = result.Id;
                    current_student = result;
                    _handle = true;
                    RefreshStudentList();
                }
                is_adding = false;
            }
            else
            {
                if (_handle && e.EditAction == DataGridEditAction.Commit)
                {
                    _handle = false;
                    studentList.CommitEdit();
                    var task = client
                        .For<Students>()
                        .Key(current_student.Id)
                        .Set(new Students { Name = (e.Row.Item as Students).Name ?? String.Empty })
                        .UpdateEntryAsync();
                    task.Wait();
                    current_student = task.Result;
                    _handle = true;
                    RefreshStudentList();
                }
            }
        }

        private void studentList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count == 0) return;
            if (e.AddedItems[0].ToString() != "{NewItemPlaceholder}")
            {
                current_student = e.AddedItems[0] as Students;
                if (students.Any(x => current_student.Id == x.Id))
                {
                    var task = client.For<Notes>().Filter(x => x.Id == current_student.Id).FindEntriesAsync();
                    task.Wait();
                    this.current_notes.Clear();
                    foreach (Notes note in task.Result)
                    {
                        this.current_notes.Add(note);
                    }
                }
                else
                {
                    current_notes = null;
                }
            }
            notesList.ItemsSource = current_notes;
        }

        private void notesList_RowEditEnding(object sender, DataGridRowEditEndingEventArgs e)
        {
            if (is_adding_note)
            {
                if (_handle_note && e.EditAction == DataGridEditAction.Commit)
                {
                    _handle_note = false;
                    notesList.CommitEdit();
                    Notes note = e.Row.Item as Notes;
                    if (current_notes.Where(x => x.Subj == note.Subj).Count() > 1)
                    {
                        current_notes.Remove(note);
                        RefreshNoteList();
                        _handle_note = true;
                        is_adding_note = false;
                        return;
                    }
                    Task<Notes> task = client
                        .For<Notes>()
                        .Set(new Notes { NoteId = GetMaxNoteId() + 1, Id = this.current_student.Id, Note = note.Note, Subj = note.Subj ?? string.Empty })
                        .InsertEntryAsync();
                    task.Wait();
                    Notes result = task.Result;
                    _handle_note = true;
                    RefreshNoteList();
                }
                is_adding_note = false;
            }
            else
            {
                if (_handle_note && e.EditAction == DataGridEditAction.Commit)
                {
                    _handle_note = false;
                    Notes temp = e.Row.Item as Notes;
                    Notes prev = Notes.CreateNotes(temp.NoteId, current_student.Id, temp.Subj, temp.Note);
                    notesList.CommitEdit();
                    Notes note = e.Row.Item as Notes;
                    if (current_notes.Where(x => x.Subj == note.Subj).Count() > 1)
                    {
                        e.Row.Item = prev;
                        RefreshNoteList();
                        _handle_note = true;
                        return;
                    }
                    note.Students = current_student;
                    prev.Students = current_student;
                    Task<Notes> task = client
                        .For<Notes>()
                        .Key(temp.NoteId)
                        .Set(note)
                        .UpdateEntryAsync();
                    task.Wait();
                    _handle_note = true;
                    RefreshNoteList();
                }
            }
        }

        private void Start_Btn_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                client = new ODataClient(new Uri("http://localhost:789/PI-POIBMS-4/Lab-06/WCFDataSimplex.svc/"));
                studentList.ItemsSource = students;
                notesList.ItemsSource = current_notes;
                _ = App.Current.Dispatcher.Invoke(async delegate
                {
                    foreach (Students item in await client
                                                      .For<Students>()
                                                      .OrderBy(x => x.Id)
                                                      .FindEntriesAsync())
                    {
                        students.Add(item);
                    };
                    this.current_student = this.students[0];
                    this.current_notes = this.current_student.Notes;
                    notesList.ItemsSource = this.current_notes;
                }
               );
                Close_Btn.IsEnabled = true;
                Start_Btn.IsEnabled = false;
            }
            catch (Exception)
            {
                client = null;
                MessageBox.Show("Can't open connection with service! Try again later.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Close_Btn_Click(object sender, RoutedEventArgs e)
        {
            current_notes.Clear();
            current_student = null;
            students.Clear();
            studentList.ItemsSource = null;
            notesList.ItemsSource = null;
            client = null;
            Start_Btn.IsEnabled = true;
            Close_Btn.IsEnabled = false;
        }
    }
}
