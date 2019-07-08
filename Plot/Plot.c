
{

  int number_of_fragments = 4;   // SSPs
  int number_of_packets = 12;    // channels in each SSP

  gStyle->SetMarkerStyle(7);
  gROOT->ForceStyle();

  //TFile f1("RawDecoder_hist_000484_2.root"); 
  TFile f1("RawDecoder_hist.root"); 
  ssprawdecoder->cd();  //Directory

  int i,j;

  // =================================================

  TCanvas *c10 = new TCanvas("c10", "Raw Decoder", 1200 , 400);
  c10->Divide(3,1);

  c10->cd(1);
  ssp_packets->Draw("AP");
  
  c10->cd(2);
  ssp_packets_frequency->Draw("");

  c10->cd(3);
  peaks->Draw("");
 
  c10->SaveAs("RawDecoder_10.png");

  c10->Destructor();
  // =================================================
  
  TCanvas *c20 = new TCanvas("c20", "Pedestal", 1920 , 1080);
  c20->Divide(4,3);

  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c20->cd(j);
      TGraph *g = (TGraph*)gDirectory->Get(Form("pedestal_event_channel_%d",i*number_of_packets+(j-1) ));
      if ( g ) g->Draw("AP"); 
    }
    c20->SaveAs(Form("RawDecoder_20_frag%d.png",i));
  }
  
  TCanvas *c30 = new TCanvas("c30", "Area", 1920 , 1080);
  c30->Divide(4,3);
  
  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c30->cd(j);
      TGraph *g = (TGraph*)gDirectory->Get(Form("area_event_channel_%d",i*number_of_packets+(j-1) ));
      if ( g ) g->Draw("AP");
    }
    c30->SaveAs(Form("RawDecoder_30_frag%d.png",i));
  }
  
  TCanvas *c40 = new TCanvas("c40", "Peak", 1920 , 1080);
  c40->Divide(4,3);
  
  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c40->cd(j);
      TGraph *g = (TGraph*)gDirectory->Get(Form("peak_event_channel_%d",i*number_of_packets+(j-1) ));
      if ( g ) g->Draw("AP");
    }
    c40->SaveAs(Form("RawDecoder_40_frag%d.png",i));
  }

  TCanvas *c50 = new TCanvas("c50", "Area vs Peak", 1920 , 1080);
  c50->Divide(4,3);
  
  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c50->cd(j);
      TGraph *g = (TGraph*)gDirectory->Get(Form("area_peak_channel_%d",i*number_of_packets+(j-1) ));
      if ( g ) g->Draw("AP");
    }
    c50->SaveAs(Form("RawDecoder_50_frag%d.png",i));
  }

  TCanvas *c60 = new TCanvas("c60", "Peaks distribution ", 1920 , 1080);
  c60->Divide(4,3);

  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c60->cd(j);
      TH1D *g = (TH1D*)gDirectory->Get(Form("peaks_channel_%d",i*number_of_packets+(j-1) ));
      if ( g ) g->Draw("");
    }
    c60->SaveAs(Form("RawDecoder_60_frag%d.png",i));
  }

  TCanvas *c65 = new TCanvas("c65", "Area distribution ", 1920 , 1080);
  c65->Divide(4,3);

  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c65->cd(j);
      TH1D *g = (TH1D*)gDirectory->Get(Form("area_channel_%d",i*number_of_packets+(j-1) ));
      if ( g ) g->Draw("");
    }
    c65->SaveAs(Form("RawDecoder_65_frag%d.png",i));
  }

  TCanvas *c70 = new TCanvas("c70", "Persistent waveform", 1920 , 1080);
  c70->Divide(4,3);

  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
    c70->cd(j);
    TH2D *h = (TH2D*)gDirectory->Get(Form("persistent_waveform_%d",i*number_of_packets+(j-1) ));
    if ( h ) {
      // h->GetYaxis()->SetRange(1600,1700);
      h->Draw("colz");
    }
    }
    c70->SaveAs(Form("RawDecoder_70_frag%d.png",i));
  }
  
  TCanvas *c80 = new TCanvas("c80", "Trigger type", 1920 , 1080);
  c80->Divide(4,3);
  
  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c80->cd(j);
      TH1D *h = (TH1D*)gDirectory->Get(Form("trigger_type_channel_%d",i*number_of_packets+(j-1) ));
      if ( h ) {
	h->SetFillColor(4);
	h->Draw();
      }
    }
    c80->SaveAs(Form("RawDecoder_80_frag%d.png",i));
  }

  TCanvas *c90 = new TCanvas("c90", "FFT", 1920 , 1080);
  c90->Divide(4,3);

  for (i=0;i<number_of_fragments;i++) {
    for (j=1;j<=number_of_packets;j++) {
      c90->cd(j);
      TH1D *h = (TH1D*)gDirectory->Get(Form("fft_channel_%d",i*number_of_packets+(j-1) ));
      if ( h ) {
	//        h->SetFillColor(4);
        h->Draw("hist");
      }
    }
    c90->SaveAs(Form("RawDecoder_90_frag%d.png",i));
  }
  

  

}
