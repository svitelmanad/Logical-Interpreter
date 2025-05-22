#pragma once

#include "blackboard.h"
#include "input.h"
#include "parser.h"
#include "validator.h"
#include "evaluator.h"
#include "Windows.h"
#include <msclr/marshal_cppstd.h>
//using namespace std;

namespace Practice 
{

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Window : public System::Windows::Forms::Form
    {
    public:
        Window(void)
        {
            InitializeComponent();
            this->Text = "Логический интерпретатор бизнес-правил";

            board = new Blackboard();
            input = new InputHandler();
            parser = new Parser();
            validator = new Validator();
            evaluator = new Evaluator();

            ProcessCommandLineArguments();
        }

    protected:
        ~Window()
        {
            if (components)
            {
                delete components;

                delete board;
                delete input;
                delete parser;
                delete validator;
                delete evaluator;
            }
        }

    private:
        System::Windows::Forms::TextBox^ inputTextBox;
        System::Windows::Forms::TextBox^ fileTextBox;
        System::Windows::Forms::RichTextBox^ outputTextBox;

        System::Windows::Forms::Button^ evaluateButton;
        System::Windows::Forms::Button^ loadFileButton;
        System::Windows::Forms::Button^ clearButton;

        System::ComponentModel::Container^ components;

        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;

        Blackboard* board;
        InputHandler* input;
        Parser* parser;
        Validator* validator;
        Evaluator* evaluator;

        void InitializeComponent(void)
        {
            this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->evaluateButton = (gcnew System::Windows::Forms::Button());
            this->outputTextBox = (gcnew System::Windows::Forms::RichTextBox());
            this->loadFileButton = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->fileTextBox = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->clearButton = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // inputTextBox
            // 
            this->inputTextBox->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->inputTextBox->BackColor = System::Drawing::Color::PeachPuff;
            this->inputTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->inputTextBox->ForeColor = System::Drawing::Color::DarkOliveGreen;
            this->inputTextBox->Location = System::Drawing::Point(13, 39);
            this->inputTextBox->Margin = System::Windows::Forms::Padding(4);
            this->inputTextBox->Multiline = true;
            this->inputTextBox->Name = L"inputTextBox";
            this->inputTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->inputTextBox->Size = System::Drawing::Size(745, 159);
            this->inputTextBox->TabIndex = 0;
            this->inputTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Window::inputTextBox_KeyPress);
            // 
            // evaluateButton
            // 
            this->evaluateButton->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->evaluateButton->BackColor = System::Drawing::Color::PeachPuff;
            this->evaluateButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->evaluateButton->ForeColor = System::Drawing::Color::DarkOliveGreen;
            this->evaluateButton->Location = System::Drawing::Point(13, 206);
            this->evaluateButton->Margin = System::Windows::Forms::Padding(4);
            this->evaluateButton->Name = L"evaluateButton";
            this->evaluateButton->Size = System::Drawing::Size(160, 42);
            this->evaluateButton->TabIndex = 1;
            this->evaluateButton->Text = L"Выполнить";
            this->evaluateButton->UseVisualStyleBackColor = false;
            this->evaluateButton->Click += gcnew System::EventHandler(this, &Window::EvaluateButton_Click);
            // 
            // outputTextBox
            // 
            this->outputTextBox->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->outputTextBox->BackColor = System::Drawing::Color::PeachPuff;
            this->outputTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->outputTextBox->ForeColor = System::Drawing::Color::DarkOliveGreen;
            this->outputTextBox->Location = System::Drawing::Point(13, 441);
            this->outputTextBox->Margin = System::Windows::Forms::Padding(4);
            this->outputTextBox->Name = L"outputTextBox";
            this->outputTextBox->ReadOnly = true;
            this->outputTextBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
            this->outputTextBox->Size = System::Drawing::Size(745, 100);
            this->outputTextBox->TabIndex = 2;
            this->outputTextBox->Text = L"";
            // 
            // loadFileButton
            // 
            this->loadFileButton->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->loadFileButton->BackColor = System::Drawing::Color::PeachPuff;
            this->loadFileButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->loadFileButton->ForeColor = System::Drawing::Color::DarkOliveGreen;
            this->loadFileButton->Location = System::Drawing::Point(13, 358);
            this->loadFileButton->Margin = System::Windows::Forms::Padding(4);
            this->loadFileButton->Name = L"loadFileButton";
            this->loadFileButton->Size = System::Drawing::Size(160, 42);
            this->loadFileButton->TabIndex = 3;
            this->loadFileButton->Text = L"Загрузить";
            this->loadFileButton->UseVisualStyleBackColor = false;
            this->loadFileButton->Click += gcnew System::EventHandler(this, &Window::LoadFileButton_Click);
            // 
            // label1
            // 
            this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->ForeColor = System::Drawing::Color::PeachPuff;
            this->label1->Location = System::Drawing::Point(11, 15);
            this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(182, 20);
            this->label1->TabIndex = 4;
            this->label1->Text = L"Введите выражение";
            // 
            // label2
            // 
            this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->ForeColor = System::Drawing::Color::PeachPuff;
            this->label2->Location = System::Drawing::Point(11, 417);
            this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(97, 20);
            this->label2->TabIndex = 5;
            this->label2->Text = L"Результат";
            // 
            // fileTextBox
            // 
            this->fileTextBox->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->fileTextBox->BackColor = System::Drawing::Color::PeachPuff;
            this->fileTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->fileTextBox->ForeColor = System::Drawing::Color::DarkOliveGreen;
            this->fileTextBox->Location = System::Drawing::Point(15, 293);
            this->fileTextBox->Margin = System::Windows::Forms::Padding(4);
            this->fileTextBox->Multiline = true;
            this->fileTextBox->Name = L"fileTextBox";
            this->fileTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->fileTextBox->Size = System::Drawing::Size(745, 57);
            this->fileTextBox->TabIndex = 6;
            this->fileTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Window::fileTextBox_KeyPress);
            // 
            // label3
            // 
            this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->ForeColor = System::Drawing::Color::PeachPuff;
            this->label3->Location = System::Drawing::Point(13, 269);
            this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(187, 20);
            this->label3->TabIndex = 7;
            this->label3->Text = L"Введите путь файла";
            // 
            // clearButton
            // 
            this->clearButton->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->clearButton->BackColor = System::Drawing::Color::PeachPuff;
            this->clearButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->clearButton->ForeColor = System::Drawing::Color::DarkOliveGreen;
            this->clearButton->Location = System::Drawing::Point(13, 549);
            this->clearButton->Margin = System::Windows::Forms::Padding(4);
            this->clearButton->Name = L"clearButton";
            this->clearButton->Size = System::Drawing::Size(160, 42);
            this->clearButton->TabIndex = 8;
            this->clearButton->Text = L"Очистить все";
            this->clearButton->UseVisualStyleBackColor = false;
            this->clearButton->Click += gcnew System::EventHandler(this, &Window::clearButton_Click);
            // 
            // Window
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::DarkOliveGreen;
            this->ClientSize = System::Drawing::Size(779, 603);
            this->Controls->Add(this->clearButton);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->fileTextBox);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->loadFileButton);
            this->Controls->Add(this->outputTextBox);
            this->Controls->Add(this->evaluateButton);
            this->Controls->Add(this->inputTextBox);
            this->Margin = System::Windows::Forms::Padding(4);
            this->MinimumSize = System::Drawing::Size(794, 537);
            this->Name = L"Window";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->ResumeLayout(false);
            this->PerformLayout();

        }

    private:

        //Обработка выражений, заданных через командную строку
        void ProcessCommandLineArguments()
        {
            array<String^>^ args = Environment::GetCommandLineArgs();
            std::vector<std::string> lines;

            for (int i = 1; i < args->Length; i++)
            {
                System::String^ str = dynamic_cast<System::String^>(args[i]);
                std::string arg = msclr::interop::marshal_as<std::string>(str);
                lines.push_back(arg);
                inputTextBox->Text += gcnew System::String(arg.c_str()) + Environment::NewLine;
            }

            if (!lines.empty())
            {
                input->readFromArguments(lines, *board);
                parser->process(*board);
                validator->validate(*board);
                evaluator->evaluate(*board);

                std::string result = board->printResult();
                outputTextBox->Text = gcnew System::String(result.c_str());
            }
        }

        //Обработка события нажатия кнопки "Выполнить"
        System::Void EvaluateButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            outputTextBox->Text = "";
            fileTextBox->Text = "";
            board->clear();

            String^ inputText = inputTextBox->Text;
            std::string stdInputText = msclr::interop::marshal_as<std::string>(inputText);

            input->readInteractive(*board, stdInputText);
            parser->process(*board);
            validator->validate(*board);
            evaluator->evaluate(*board);

            std::string result = board->printResult();
            outputTextBox->Text += gcnew System::String(result.c_str());

        }

        //Обработка события нажатия кнопки "Загрузить"
        System::Void LoadFileButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            inputTextBox->Text = "";
            outputTextBox->Text = "";
            board->clear();

            String^ text = fileTextBox->Text;
            std::string file_name = msclr::interop::marshal_as<std::string>(text);
            std::vector<std::string> lines = input->readFromFile(file_name, *board);

            for (size_t i = 0; i < lines.size(); i++)
            {
                inputTextBox->Text += gcnew System::String(lines[i].c_str()) + Environment::NewLine;
            }

            parser->process(*board);
            validator->validate(*board);
            evaluator->evaluate(*board);

            std::string result = board->printResult();
            outputTextBox->Text = gcnew System::String(result.c_str());
        }


    //Очистка полей ввода выражения или названия файла
    private: System::Void inputTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) 
    {
        fileTextBox->Text = "";

        if (Char::IsControl(e->KeyChar))
            return;

        if ((e->KeyChar >= L'А' && e->KeyChar <= L'я') || e->KeyChar == L'ё' || e->KeyChar == L'Ё')
        {
            e->Handled = true;
            return;
        }

        int charCode = (int)e->KeyChar;
        if ((charCode >= 1040 && charCode <= 1103) || charCode == 1025 || charCode == 1105)
        {
            e->Handled = true;
            return;
        }
    }
    private: System::Void fileTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) 
    {
        inputTextBox->Text = "";
    }

    //Обработка после кнопки "Очистить все"
    private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) 
    {
        fileTextBox->Text = "";
        inputTextBox->Text = "";
        outputTextBox->Text = "";
    }
};
}