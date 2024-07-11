#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <iostream>
#include <cstdio>  // snprintf를 사용하기 위해 포함

void analysis_allchperdet2()
{
    auto file = new TFile("data/RUN511.ch.root", "read");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    
    auto tree = (TTree*)file->Get("channels");
    if (!tree) {
        std::cerr << "Error getting TTree" << std::endl;
        file->Close();
        return;
    }

    auto cvs = new TCanvas("cvs", "cvs", 800, 800);
    cvs->Divide(3, 1);  // 캔버스를 3개의 패드로 나누기

    for (int dch = 1; dch <= 32; ++dch) {
        for (int det = 2; det < 5; ++det) {
            cvs->cd(det-1);  // 올바른 패드로 전환
            gPad->Clear();  // 패드 초기화
            
            char hist_name[50];
            snprintf(hist_name, sizeof(hist_name), "hist_dch%d_det%d", dch, det);
            auto hist = new TH1D(hist_name, hist_name, 50, 1000, 5000);

            char draw_command[100];
            snprintf(draw_command, sizeof(draw_command), "adc>>%s", hist_name);
            char selection[50];
            snprintf(selection, sizeof(selection), "det==%d && dch==%d", det, dch);

            tree->Draw(draw_command, selection, "");

            auto fit = new TF1("fit", "gaus(0)", 1530, 1600);
            hist->Fit(fit);
            
           
        }
        // 각 dch 값에 대해 캔버스를 저장
        char save_name[50];
        snprintf(save_name, sizeof(save_name), "Channel_%d_per_det.png", dch);
        cvs->SaveAs(save_name);
    }

    file->Close();
}

