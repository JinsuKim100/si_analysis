#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <iostream>

void draw_summary() {
    // ROOT 파일 열기
    TFile *file = TFile::Open("data/RUN511.ch.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    // TTree 가져오기
    TTree *tree = nullptr;
    file->GetObject("channels", tree);
    if (!tree) {
        std::cerr << "Error getting TTree" << std::endl;
        file->Close();
        return;
    }

    // TCanvas 생성 및 분할
    TCanvas *cvs = new TCanvas("cvs", "cvs", 1200, 750);
    cvs->Divide(2, 2);

    // 브랜치 이름 배열
    const char* branches[] = {"adc", "det", "dch"};

    // 각 브랜치에 대해 그래프 그리기
    for (int i = 0; i < 3; ++i) {
        std::cout << i << " cvs_" << branches[i] << std::endl;
        cvs->cd(i + 1);
        tree->Draw(branches[i]);
    }

    // 캔버스 저장 (옵션)
    // cvs->SaveAs("output.png");

    // 파일 닫기
    file->Close();
}

