#include "updatedialog.h"

string ID;
//TODO:Change the third parameter to the object of type equivalent to testUser 
updateDialog :: updateDialog(wxWindow* parent, wxString title ,RData& user)
              : userDialog(title, parent){
 ID = user.id;
 name_text->ChangeValue(user.name);
 email_text->ChangeValue(user.email);
 phone_text->ChangeValue(user.phone);
 address_text->ChangeValue(user.address);
 
 if(string(user.gender) == "Female"){
   gen_male->SetValue(false);
   gen_others->SetValue(false);
   gen_female->SetValue(true);
 }
 else if(string(user.gender) == "Others"){
   gen_male->SetValue(false);
   gen_female->SetValue(false);
   gen_others->SetValue(true);

 }
 else if(string(user.gender) == "Male"){
   
    gen_female->SetValue(false);
    gen_others->SetValue(false);
    gen_male->SetValue(true);  
 
  }
  //pass in the file name (PNG or JPG) and this functions sets that image file as profile picture of the user
  setProfile(user.file_path);

}

void updateDialog:: onBtnClick(wxCommandEvent& event){

//Input validation begins here

//check if all text box are filled at least!
  if(name_text->GetLineLength(0) < 1 || email_text->GetLineLength(0) < 1 || address_text->GetLineLength(0) < 1 || phone_text->GetLineLength(0) < 1){
    wxMessageDialog* error_dialog = new wxMessageDialog(this, wxT("All the input fields are necessary"), wxT("Error"), wxOK | wxICON_ERROR);
    error_dialog->ShowModal();
    return;
 }

 //check if email has a '@' and '.' symbol
  wxString check_email =  email_text->GetLineText(0);
  int count = 0;
  int len = 0;
 for(char elt : check_email){
   if(elt == '@' || elt == '.') count ++;
   len ++;
 }

 if(count < 2 || len < 8 ){
  wxMessageDialog* error_dialog = new wxMessageDialog(this, wxT(" Your email is invalid "), wxT("Error"), wxOK | wxICON_ERROR);
    error_dialog->ShowModal();
    return;

 }

//check if phone number is valid

  if(phone_text->GetLineLength(0) != 10){

 wxMessageDialog* error_dialog = new wxMessageDialog(this, wxT(" Your phone number is invalid "), wxT("Error"), wxOK | wxICON_ERROR);
    error_dialog->ShowModal();
    return;

 }

 wxString no = phone_text->GetLineText(0);
  std::string num = std::string(no.mb_str());
 
//Checks whether the input phone number is digit
  for(char elt : no){
 
    if(!isdigit(elt)){
      wxMessageDialog* message = new wxMessageDialog(this, wxT("Phone number should be digits"), wxT("Error"), wxOK | wxICON_ERROR);
       message->ShowModal();
       return;
    }
  }

//Input validation ends here

 wxMessageDialog* message = new wxMessageDialog(this, "Changes will be Saved", "Confirm", wxOK | wxCANCEL);
 if(message->ShowModal() == wxID_OK){
    //sends the updated data to database

     //Gets the input data and covert to std::string
      std::string name = std::string(name_text -> GetLineText(0).mb_str());
      std::string email = std::string(email_text -> GetLineText(0).mb_str());
      std::string phone= std::string(phone_text -> GetLineText(0).mb_str());
      std::string address = std::string(address_text -> GetLineText(0).mb_str());
       
      std::string gender;
      if(gen_male->GetValue()) gender = "Male";
      else if (gen_female -> GetValue()) gender = "Female";
      else gender = "Others";

      //  std::string image_path = std::string(selectFile->GetPath().mb_str());

       string file;
    //   if(image_path.size()>0)
    // file = string(image_path);
    // else
      file = "./media/default_pp.jpg";
      
        //  TODO:1.Call the updateUser function and pass above data

          User usr(name, email, address, phone, gender, file);
         bool success = usr.updateUser(ID);
          
           if(!success){
             wxMessageDialog* message = new wxMessageDialog(this, "User cannot be updated", "Error", wxOK | wxICON_ERROR);
            if( message -> ShowModal() == wxID_OK) 
            Destroy();
            return;
            
          }
            
          wxMessageDialog* message = new wxMessageDialog(this, "User updated successfully", "Success", wxOK);
          if(message -> ShowModal() == wxID_OK)
             Destroy();
             return;
      
 }
}

void updateDialog :: onCancel (wxCommandEvent& event){

 wxMessageDialog* message = new wxMessageDialog(this, "No User will be updated", "Cancel", wxOK | wxCANCEL);
 if(message -> ShowModal() == wxID_OK){
   Destroy();
   return;
 }

}

void updateDialog :: showDialog(){

  ShowModal();

}
