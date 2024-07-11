#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <iostream>

void analysis_allch()
{
    auto file = new TFile("data/RUN511.ch.root","read");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    
    auto tree = (TTree*) file->Get("channels");
    if (!tree) {
        std::cerr << "Error getting TTree" << std::endl;
        file->Close();
        return;
    }

    for (int dch = 1; dch <= 30; ++dch) {
        std::string canvas_name = "cvs_" + std::to_string(dch);
        std::string hist_name = "hist_" + std::to_string(dch);
        
        auto cvs = new TCanvas(canvas_name.c_str(), canvas_name.c_str(), 800, 600);
        auto hist = new TH1D(hist_name.c_str(), "Histogram per channel;ADC;Count", 50, 1450, 1600);
        
        std::string draw_command = "adc>>" + hist_name;
        std::string cut_command = "det==2 && dch==" + std::to_string(dch);
        
        tree->Draw(draw_command.c_str(), cut_command.c_str(), "");
        
        auto fit = new TF1("fit", "gaus(0)", 1530, 1600);
        hist->Fit(fit);
        
        // Optional: Save each canvas as an image
        std::string save_name = "det2&dch" + std::to_string(dch) + ".png";
        cvs->SaveAs(save_name.c_str());
    }

    file->Close();
}
