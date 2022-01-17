#include "wx/wx.h"
#include "deletedialog.h"


// #ifndef testUser_h
//   #define testUser_h

//     class testUser{
//       public:
//      wxString id, name, gender, email, phone, address, path;

//        testUser();
//        testUser(wxString i, wxString n, wxString g, wxString e, wxString p, wxString add, wxString image_path);

//     };


// #endif

string name;

deleteDialog :: deleteDialog (wxWindow* parent, RData& usr, wxString title)
              : updateDialog(parent, title,  usr){

name = usr.name;

}

void deleteDialog :: showDialog(){

 ShowModal();

}
User usere;
void deleteDialog :: onBtnClick(wxCommandEvent& event){

  wxMessageDialog* message = new wxMessageDialog(this, "Delete this User?","Confirm",wxOK | wxCANCEL);
  if(message -> ShowModal() == wxID_OK){
    bool success = usere.removeUser(name);

    if (!success){
      wxMessageDialog* message = new wxMessageDialog(this, "User can not be Deleted!!","Error",wxOK);
      message -> ShowModal();
      return;
    }
    else{
      wxMessageDialog* message = new wxMessageDialog(this, "User Deleted Succesfully!!","Succcess",wxOK);
      message -> ShowModal();
      Destroy();
      return;
    }
  }
    // this->Destroy();
    return;
  
}

void deleteDialog :: onCancel(wxCommandEvent& event){

 wxMessageDialog* warning = new wxMessageDialog(this, "No User will be deleted", "Confirm", wxOK | wxCANCEL);
 if(warning->ShowModal() == wxID_OK);
  Destroy();
  return;
}
