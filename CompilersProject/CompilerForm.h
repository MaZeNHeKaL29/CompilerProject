#pragma once

#include "TinyScanner.h"

#using <system.drawing.dll>

namespace CompilersProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for CompilerForm
	/// </summary>
	public ref class CompilerForm : public System::Windows::Forms::Form
	{
	public:
		CompilerForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CompilerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ code;
	private: System::Windows::Forms::RichTextBox^ tokensList;
	protected:

	protected:

	private: System::Windows::Forms::Button^ save;

	private: System::Windows::Forms::Button^ browse;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;



	private: Stream^ myStream;
	private: StreamWriter^ myStreamWriter;
	private: String^ strFileName;
	private: String^ strCodeContent;
	private: System::Windows::Forms::Button^ findTokens;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->code = (gcnew System::Windows::Forms::RichTextBox());
			this->tokensList = (gcnew System::Windows::Forms::RichTextBox());
			this->save = (gcnew System::Windows::Forms::Button());
			this->browse = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->findTokens = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// code
			// 
			this->code->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->code->ForeColor = System::Drawing::SystemColors::WindowText;
			this->code->Location = System::Drawing::Point(12, 50);
			this->code->Name = L"code";
			this->code->Size = System::Drawing::Size(395, 440);
			this->code->TabIndex = 0;
			this->code->Text = L"";
			this->code->TextChanged += gcnew System::EventHandler(this, &CompilerForm::code_TextChanged);
			// 
			// tokensList
			// 
			this->tokensList->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tokensList->Location = System::Drawing::Point(450, 50);
			this->tokensList->Name = L"tokensList";
			this->tokensList->ReadOnly = true;
			this->tokensList->Size = System::Drawing::Size(395, 385);
			this->tokensList->TabIndex = 1;
			this->tokensList->Text = L"";
			// 
			// save
			// 
			this->save->Location = System::Drawing::Point(731, 471);
			this->save->Name = L"save";
			this->save->Size = System::Drawing::Size(114, 39);
			this->save->TabIndex = 2;
			this->save->Text = L"Save";
			this->save->UseVisualStyleBackColor = true;
			this->save->Click += gcnew System::EventHandler(this, &CompilerForm::save_Click);
			// 
			// browse
			// 
			this->browse->Location = System::Drawing::Point(596, 471);
			this->browse->Name = L"browse";
			this->browse->Size = System::Drawing::Size(114, 39);
			this->browse->TabIndex = 3;
			this->browse->Text = L"Browse";
			this->browse->UseVisualStyleBackColor = true;
			this->browse->Click += gcnew System::EventHandler(this, &CompilerForm::browse_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// findTokens
			// 
			this->findTokens->Location = System::Drawing::Point(461, 471);
			this->findTokens->Name = L"findTokens";
			this->findTokens->Size = System::Drawing::Size(114, 39);
			this->findTokens->TabIndex = 4;
			this->findTokens->Text = L"Find Tokens";
			this->findTokens->UseVisualStyleBackColor = true;
			this->findTokens->Click += gcnew System::EventHandler(this, &CompilerForm::findTokens_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 37);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Code";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(447, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(214, 37);
			this->label2->TabIndex = 6;
			this->label2->Text = L"List of Tokens";
			// 
			// CompilerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(863, 522);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->findTokens);
			this->Controls->Add(this->browse);
			this->Controls->Add(this->save);
			this->Controls->Add(this->tokensList);
			this->Controls->Add(this->code);
			this->Name = L"CompilerForm";
			this->Text = L"CompilerForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void browse_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->InitialDirectory = Directory::GetCurrentDirectory();
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			myStream = openFileDialog1->OpenFile();
			if ((myStream != nullptr))
			{
				strFileName = openFileDialog1->FileName;
				strCodeContent = File::ReadAllText(strFileName);
				code->Text = File::ReadAllText(strFileName);
				myStream->Close();
			}
		}
	}
	private: System::Void save_Click(System::Object^ sender, System::EventArgs^ e) {
		myStreamWriter = gcnew StreamWriter("tinyLanguageSample.tl");
		myStreamWriter->Write(code->Text);
		strFileName = "tinyLanguageSample.tl";
		myStreamWriter->Close();
		strCodeContent = File::ReadAllText(strFileName);
	}
private: System::Void findTokens_Click(System::Object^ sender, System::EventArgs^ e) {
	scanCode(strCodeContent);
	String^ strTokensList;
	printTokens(strTokensList);
	tokensList->Text = strTokensList;
}
private: System::Void code_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	strCodeContent = code->Text;
}
};
}
