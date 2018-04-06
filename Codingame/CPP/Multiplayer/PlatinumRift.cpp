// Rank: 113/133 - Gold League 

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#include <algorithm> 
#include <time.h> 


int prospotenssiin(int x, int pr, int pow) {
    if (pow > 6 || x == 0) return(0);
    double tulos = (double)x;
    for (int tt = 0; tt < pow; ++tt)
        tulos = tulos * pr / 100.0;
    return(std::floor(tulos));
}


struct Manner {
    std::set<int> alusta(int id, std::vector<int> alut, std::vector<int> loput, std::vector<int> tuotot);
    std::set<int> idt;
    std::map<std::pair<int, int>, int > etaisyydet;
    int platinaa;
    std::set<int> alueet() const {return(idt);}
    int matka(int alkuId, int loppuId);
    std::set<int> nollan_arvoiset(std::vector<int> houk);
    std::set<int> muiden(std::vector<int> omis, int oma);
  private:
    void laske_dt(std::map<std::pair<int, int>, int> & etaisyydet, int id, std::vector<int> alut, std::vector<int> loput, int alueita);
};
std::set<int> Manner::alusta(int id, std::vector<int> kaikki_alut, std::vector<int> kaikki_loput, std::vector<int> tuotot) {
    std::set<int> tulos, uudet;
    tulos.insert(id);
    uudet.insert(id);
    while (uudet.size()>0) {
        std::set<int> apu;
        for (std::set<int>::iterator it=uudet.begin(); it!=uudet.end(); ++it) {
            for (int ss = 0; ss < kaikki_alut.size(); ++ss) {
                if (*it == kaikki_alut[ss] && tulos.count(kaikki_loput[ss])==0) {
                    tulos.insert(kaikki_loput[ss]);
                    apu.insert(kaikki_loput[ss]);
                }
                if (*it == kaikki_loput[ss] && tulos.count(kaikki_alut[ss])==0) {
                    tulos.insert(kaikki_alut[ss]);
                    apu.insert(kaikki_alut[ss]);
                }
            }
        }
        uudet = apu;
    }
    idt = tulos;
    std::map<std::pair<int, int>, int> etais;
    for (std::set<int>::iterator lahtop = tulos.begin(); lahtop != tulos.end(); ++lahtop)
        laske_dt(etais, *lahtop, kaikki_alut, kaikki_loput, idt.size());
    etaisyydet = etais;
    platinaa = 0;
    for (std::set<int>::iterator it=tulos.begin(); it!=tulos.end(); ++it)
        platinaa = platinaa + tuotot[*it];
    return (tulos);
}
int Manner::matka(int alkuId, int loppuId) {
    if (idt.count(alkuId) == 0 || idt.count(loppuId) == 0) {
        return(10000); 
        std::cerr << "HEP! Distancias requeridas del continente equivocado... " << alkuId << " ja " << loppuId << std::endl;
    }
    return(etaisyydet[std::pair<int, int> (alkuId,loppuId)]);
}
void  Manner::laske_dt(std::map<std::pair<int, int>, int> & etaisyydet, int id, std::vector<int> kaikki_alut, std::vector<int> kaikki_loput, int alueita) {
    std::set<int> jo_loydetyt, edelliset, uusimmat;
    jo_loydetyt.insert(id);
    edelliset.insert(id);
    etaisyydet[std::pair<int, int> (id, id)] = 0;
    int et_nyt = 1;
    while (edelliset.size() > 0) {
        for (std::set<int>::iterator valietappi = edelliset.begin(); valietappi != edelliset.end(); ++valietappi) {
            for (int tt = 0; tt < kaikki_alut.size(); ++tt) {
                if (kaikki_alut[tt] == *valietappi && jo_loydetyt.count(kaikki_loput[tt]) == 0) {
                    uusimmat.insert(kaikki_loput[tt]);
                    jo_loydetyt.insert(kaikki_loput[tt]);
                }
                if (kaikki_loput[tt] == *valietappi && jo_loydetyt.count(kaikki_alut[tt]) == 0) {
                    uusimmat.insert(kaikki_alut[tt]);
                    jo_loydetyt.insert(kaikki_alut[tt]);
                }
            }
        }
        for (std::set<int>::iterator uusi = uusimmat.begin(); uusi != uusimmat.end(); ++uusi) {
            etaisyydet[std::pair<int, int>(*uusi, id)] = et_nyt;
            etaisyydet[std::pair<int, int>(id, *uusi)] = et_nyt;
        }
        edelliset = uusimmat;
        uusimmat.clear();
        ++et_nyt;
        if (et_nyt > 40) {
            std::cerr << "¡No se pueden calcular distancias!" << std::endl;
            return;
        }
        }
}
std::set<int> Manner::nollan_arvoiset(std::vector<int> houk) {
    std::set<int> tulos;
    for (std::set<int>::iterator it=idt.begin(); it!=idt.end(); ++it)
        if (houk[*it] == 0)
            tulos.insert(*it);
    return(tulos);    
}
std::set<int> Manner::muiden(std::vector<int> omis, int oma) {
    std::set<int> tulos;
    for (std::set<int>::iterator it=idt.begin(); it!=idt.end(); ++it)
        if (omis[*it] != oma)
            tulos.insert(*it);
    return(tulos);
}


bool operator < ( Manner const &o, Manner const &v) {
    if (v.idt.size() < o.idt.size())
        return(true);
    return(*v.idt.begin() < *o.idt.begin());
}


struct Liikkeet {
    Liikkeet() {}
    Liikkeet(std::vector<int> l, std::vector<int> k, std::vector<int> m) : lkmt(m), lahto(l), kohde(k) {}    
    std::vector<int> lkmt;
    std::vector<int> lahto;
    std::vector<int> kohde;
    void lisaa_liike(int id_mista, int id_mihin, int paljonko = 1);
};
void Liikkeet::lisaa_liike(int id_mista, int id_mihin, int paljonko ) {
    if (paljonko==0)
        return;
    int tt =0;
    bool kesken = true;
    while (kesken && tt < lkmt.size()) {
        if (lahto[tt] == id_mista && kohde[tt] == id_mihin) {
            ++lkmt[tt];
            kesken = false;
        }
        ++tt;
    }
    if (kesken) {
        lkmt.push_back(paljonko);
        lahto.push_back(id_mista);
        kohde.push_back(id_mihin);
    }
}


class Infot {
    int playerCount;
    int myId;
    std::vector < int > idt;
    std::vector < int > platinatuotot;
    std::vector < int > loput;
    std::vector < int > alut;
    std::vector < int > omistajat;
    std::vector < int > vihut;
    std::vector < int > omat;
    int platinum;   
    int vro;
    std::vector <int> houkuttelevuudet;
    std::set<Manner> mantereet;
    std::vector<int> jrj(std::vector<int> ehdokkaat, std::vector<int> ehdokkaiden_arvot);
    std::vector<int> omistukset(std::vector<int> ehdokkaat, int kenen);
    std::vector<int> laske_pohjahoukuttelevuudet(std::vector<int> ehdokkaat);
    std::vector<int> laske_verkostohoukuttelevuudet(Manner manner, std::vector<int> jo_olemassa, std::vector<int> pohjahoukuttelevuudet);
    bool altisko(int id);
    bool valmis_mannerko(Manner manner);
    void omalta_alueelta_ohjaaminen(int id);
  public:
    Infot();
    Infot ( int pelaajia, int omaId,
            std::vector<int> peliruudut, std::vector<int> platinatuotot,
            std::vector<int> alkupisteet, std::vector<int> loppupisteet);
    void kierroksen_alku(std::vector < int > omistajat, std::vector < int > vihut, std::vector < int > omat, int platinaa, std::set<int> pelaajat);
    bool eka_kierrosko() {return(vro==1);}
    int pelaajia() {return(playerCount);}
    std::vector<int> parhaat_alueet(int kenen); 
    std::vector<int> joukkoja(int kenen); 
    int varaa() {return(platinum);}
    int montako_omaa(int id) {return(omat[id]);}
    std::vector<int> suunnat(int id, int moneenko_suuntaan);
    int maksa(int paljonko, int mihin);
    std::vector<int> naapurit(int id);
    int houkutus(int id) {return(houkuttelevuudet[id]);}
    std::set<Manner> poista_valmiit_mantereet();
    int uhattunako(int id);
    void lisaa_mannerten_painoarvot();
    Manner mika_manner(int id);
    std::vector<int> tuotot() {return(platinatuotot);}
    void liikkeiden_vaikutukset(Liikkeet liikkeet);
    void kierroksen_puolivali(Liikkeet liikkeet);
};

Infot::Infot() {}
Infot::Infot(int pelaajia, int id, std::vector<int> it, std::vector<int> tuotot, std::vector<int> lop, std::vector<int> alk) 
:  vro(0),
  playerCount(pelaajia),
  myId(id),
  idt(it),
  platinatuotot(tuotot),
  loput(lop),
  alut(alk)
{
    idt = jrj(idt, platinatuotot);
    std::set<Manner> uusi_kokoelma;
    std::vector<int> apu;
    std::vector<int> jaljella(idt);
    while (jaljella.size() > 0) {
        apu.clear();
        Manner uusi;
        std::set<int> menneet = uusi.alusta(jaljella[0], alut, loput, platinatuotot);
        uusi_kokoelma.insert(uusi);
        for (int tt = 0; tt < jaljella.size(); ++tt)
            if (menneet.count(jaljella[tt])==0)
                apu.push_back(jaljella[tt]);
        jaljella = apu;
    }
    mantereet = uusi_kokoelma;
}

void Infot::kierroksen_alku(std::vector<int> om, std::vector<int> vih, std::vector<int> o, int platinaa, std::set<int> pelaajia_viela) {
    ++vro; 
    omistajat = om;
    vihut = vih;
    omat = o;
    platinum = platinaa;
    std::vector<int> pohjaht = laske_pohjahoukuttelevuudet(idt);
    std::vector<int> jo(platinatuotot.size(), 0);
    mantereet = poista_valmiit_mantereet();
    for (std::set<Manner>::iterator it = mantereet.begin(); it != mantereet.end(); ++it) {
        jo = laske_verkostohoukuttelevuudet(*it, jo, pohjaht);
    }
    houkuttelevuudet = jo;
    if (vro>2)
        playerCount = pelaajia_viela.size();
}
void Infot::kierroksen_puolivali(Liikkeet liikkeet) {
    lisaa_mannerten_painoarvot();
    liikkeiden_vaikutukset(liikkeet);
    std::vector<int> pohjaht = laske_pohjahoukuttelevuudet(idt);
    std::vector<int> jo(platinatuotot.size(), 0);
    for (std::set<Manner>::iterator it = mantereet.begin(); it != mantereet.end(); ++it) {
        jo = laske_verkostohoukuttelevuudet(*it, jo, pohjaht);
    }
    houkuttelevuudet = jo;
}
std::vector<int> Infot::parhaat_alueet(int kenen) {
    if (kenen == 0)
        kenen = myId;
    std::vector<int> tulos = omistukset(idt, kenen);
    if (kenen == myId) {
        std::vector<int> apu = omistukset(idt, -1);
        tulos.insert(tulos.end(), apu.begin(), apu.end());
    }
    if (kenen == -1) {
        std::vector<int> apu;
        for (int tt = 0; tt < tulos.size(); ++tt)
            if (platinatuotot[tulos[tt]]>1)
                apu.push_back(tulos[tt]);
        tulos = apu;
    }
    if (kenen == -1) { 
        std::vector<int> apu;
        for (int tt = 0; tt < tulos.size(); ++tt)
            if (!uhattunako(tulos[tt]))
                apu.push_back(tulos[tt]);
        tulos = apu;
    }
    return(jrj(tulos, houkuttelevuudet));
}
std::vector<int> Infot::omistukset(std::vector<int> ehdokkaat, int kenen) {
    std::vector<int> tulos;
    for (int tt = 0; tt < ehdokkaat.size(); ++tt)
        if (omistajat[ehdokkaat[tt]] == kenen)
            tulos.push_back(ehdokkaat[tt]);
    return(tulos);
}
std::vector<int> Infot::laske_pohjahoukuttelevuudet(std::vector<int> ehd) {
    int hyokkaavyys = 120;
    std::vector<int> tulos(platinatuotot.size());
    for (int tt = 0; tt < ehd.size(); ++tt) {
        if (omistajat[ehd[tt]] != myId) {
            if (omistajat[ehd[tt]] == -1) {
                tulos[ehd[tt]] = 200 * platinatuotot[ehd[tt]] + hyokkaavyys;
            } else {
                tulos[ehd[tt]] = (100 + 40 * (4 - playerCount))  * platinatuotot[ehd[tt]] + hyokkaavyys;
                if (!uhattunako(ehd[tt])) {
                    tulos[ehd[tt]] = 2 * tulos[ehd[tt]];
                }
                if (vihut[ehd[tt]]==0) {
                    tulos[ehd[tt]] = 2 * tulos[ehd[tt]];
                }
            }
        }
        if (omistajat[ehd[tt]] == myId) {
            tulos[ehd[tt]] = 20 * platinatuotot[ehd[tt]];
            if (uhattunako(ehd[tt])) {
                tulos[ehd[tt]] = tulos[ehd[tt]] * 21 + 60;
            }
            if (!altisko(ehd[tt])) {
                tulos[ehd[tt]] = 0;
            }
        }
    }
    return(tulos);
}
void Infot::lisaa_mannerten_painoarvot() {
    for (std::set<Manner>::iterator it = mantereet.begin(); it != mantereet.end(); ++it) {
        if (!valmis_mannerko(*it)) {
            std::set<int> al = (*it).alueet();
            for (std::set<int>::iterator al_it = al.begin(); al_it != al.end(); ++al_it)
                houkuttelevuudet[*al_it] += (*it).platinaa;
        }
    }
}
std::vector<int> Infot::laske_verkostohoukuttelevuudet(Manner manner, std::vector<int> jo, std::vector<int> pohjaht) {
    if (valmis_mannerko(manner)) return(jo);
    int osuus = 15; 
    std::set<int> alueet = manner.alueet();
    for (std::set<int>::iterator it = alueet.begin(); it != alueet.end(); ++it) {
        int houk = pohjaht[*it];
        for (std::set<int>::iterator muut_it = alueet.begin(); muut_it != alueet.end(); ++muut_it) {
            jo[*muut_it] += prospotenssiin(houk, osuus, manner.matka(*it, *muut_it));
        }
    }
    return(jo);
}

int Infot::maksa(int x, int id) {
    platinum -= x;
    houkuttelevuudet[id] = houkuttelevuudet[id]*2/3;
    return(platinum);
}
std::vector<int> Infot::jrj(std::vector<int> ehdokkaat, std::vector<int> arvot) {
    if (ehdokkaat.size() < 2) return(ehdokkaat);
    int mx = 0;
    std::vector<int> lisattavat, hannille, tulos;
    for (int tt =0; tt < ehdokkaat.size(); ++tt) {
        mx = std::max(mx, arvot[ehdokkaat[tt]]);
    }
    for (int tt =0; tt < ehdokkaat.size(); ++tt) {
        if (mx == arvot[ehdokkaat[tt]]) {
            lisattavat.push_back(ehdokkaat[tt]);
        } else {
            hannille.push_back(ehdokkaat[tt]);
        }
    }
    hannille = jrj(hannille, arvot);
    tulos.reserve( lisattavat.size() + hannille.size() ); 
    tulos.insert( tulos.end(), lisattavat.begin(), lisattavat.end() );
    tulos.insert( tulos.end(), hannille.begin(), hannille.end() );
    return(tulos);
}
std::vector<int> Infot::joukkoja(int kenen) {
    std::vector<int> tulos;
    if (kenen)  {
        for (int tt = 0; tt < idt.size(); ++tt) 
            if (vihut[idt[tt]] > 0)
                tulos.push_back(idt[tt]);
    } else {
        for (int tt = 0; tt < idt.size(); ++tt) 
            if (omat[idt[tt]] > 0) 
                tulos.push_back(idt[tt]);
    }
    return(tulos);
}
std::vector<int> Infot::suunnat(int id, int moneenko_suuntaan) {
    std::vector<int> tulos;
    std::vector<int> ehdokkaat = naapurit(id);
    ehdokkaat.push_back(id); 
    reverse(ehdokkaat.begin(), ehdokkaat.end());
    ehdokkaat = jrj(ehdokkaat, houkuttelevuudet);
    while (ehdokkaat.size()>0 && houkuttelevuudet[ehdokkaat[ehdokkaat.size()-1]]==0)
        ehdokkaat.pop_back();
    if (ehdokkaat.size() == 0) {
        omalta_alueelta_ohjaaminen(id);
        return(suunnat(id, 1));
    }
    while (ehdokkaat.size()>1 && houkuttelevuudet[ehdokkaat[ehdokkaat.size()-1]]<20)
        ehdokkaat.pop_back();
    moneenko_suuntaan = std::min((int)ehdokkaat.size(), moneenko_suuntaan);
    for (int tt = 0; tt < moneenko_suuntaan; ++tt) {
        tulos.push_back(ehdokkaat[tt]);
        if (vihut[ehdokkaat[tt]]==0) houkuttelevuudet[ehdokkaat[tt]] /= 2; 
    }
    return(tulos);
}
void Infot::omalta_alueelta_ohjaaminen(int id) {
    Manner mann = mika_manner(id);
    std::set<int> omat = mann.nollan_arvoiset(houkuttelevuudet);
    std::set<int> kohteet = mann.muiden(omistajat, myId);
    while (kohteet.size() > 0) {
        int kohde = *(kohteet.begin());
        for (std::set<int>::iterator it = omat.begin(); it != omat.end(); ++it) {
            int tarjolla = 19 - mann.matka(kohde, *it);
            if (houkuttelevuudet[*it] < tarjolla)
                houkuttelevuudet[*it] = tarjolla;
        }
        std::set<int> seuraavat_kohteet = kohteet;
        for (std::set<int>::iterator it = kohteet.begin(); it != kohteet.end(); ++it)
            if (mann.matka(kohde, *it) < 3)
                seuraavat_kohteet.erase(*it);
        kohteet = seuraavat_kohteet;
    }
}
std::vector<int> Infot::naapurit(int id) {
    std::vector<int> tulos;
    for (int tt = 0; tt < alut.size(); ++tt) {
        if (alut[tt] == id)
            tulos.push_back(loput[tt]);
        if (loput[tt] == id)
            tulos.push_back(alut[tt]);
    }
    return(tulos);        
}
int Infot::uhattunako(int id) {
    int tulos = vihut[id];
    std::vector<int> naaps = naapurit(id);
    for (int tt = 0; tt < naaps.size(); ++tt)
        tulos += vihut[naaps[tt]];
    return(tulos);
}
bool Infot::altisko(int id) {
    bool tulos = false;
    std::vector<int> naaps = naapurit(id);
    for (int tt = 0; tt < naaps.size(); ++tt) 
        if (omistajat[naaps[tt]] != myId) 
            tulos = true;
    return(tulos);
}
std::set<Manner> Infot::poista_valmiit_mantereet() {
    std::set<Manner> tulos;
    for (std::set<Manner>::iterator it = mantereet.begin(); it != mantereet.end(); ++it) {
        if (valmis_mannerko(*it)) {
            std::set<int> poistettavat = (*it).alueet();
            std::vector<int> karsitut_idt, karsitut_alut, karsitut_loput;
            for (int tt = 0; tt < idt.size(); ++tt)
                if (poistettavat.count(idt[tt]) == 0)
                    karsitut_idt.push_back(idt[tt]);
            for (int tt = 0; tt < alut.size(); ++tt)
                if (poistettavat.count(alut[tt]) == 0 && poistettavat.count(loput[tt]) == 0) {
                    karsitut_alut.push_back(alut[tt]);
                    karsitut_loput.push_back(loput[tt]);
                }
            idt = karsitut_idt;
            alut = karsitut_alut;
            loput = karsitut_loput;
        } else {
            tulos.insert(*it);
        }
    }
    return(tulos);
}
bool Infot::valmis_mannerko(Manner manner) {
    std::set<int> alueet = manner.alueet();
    std::set<int>::iterator it = alueet.begin();
    int ekan_omistaja = omistajat[*it];
    bool ei_omia = true;
    bool ei_vihuja = true;
    while (it != alueet.end() && (ei_omia || ei_vihuja) ) {
        if (omistajat[*it] == -1 || omistajat[*it] == myId)
            ei_omia = false;
        if (omistajat[*it] != myId || vihut[*it]>0)
            ei_vihuja = false;
        ++it;
    }
    return(ei_omia || ei_vihuja);
}
Manner Infot::mika_manner(int id) {
    for (std::set<Manner>::iterator it = mantereet.begin(); it != mantereet.end(); ++it) {
        if ( (*it).alueet().count(id) > 0 )
            return(*it);
    }
    std::cerr << "¡Error!" << id << " no pertenece a ningún continente!" << std::endl;
    Manner tulos;
    return(tulos);
}
void Infot::liikkeiden_vaikutukset(Liikkeet liik) {
    if (liik.lkmt.size()) {
        for (int tt = 0; tt < liik.lkmt.size(); ++tt) {
            omat[liik.lahto[tt]] -= liik.lkmt[tt];
            omat[liik.kohde[tt]] += liik.lkmt[tt];
        }
    }
}


struct Ostot {
    Ostot() {}
    Ostot(std::vector<int> e, std::vector<int> t) : lkmt(e), indeksit(t) {}    
    std::vector<int> lkmt;
    std::vector<int> indeksit;
    void lisaa_idlle(int id, int paljonko = 1);
};
void Ostot::lisaa_idlle(int id, int paljonko ) {
    if (paljonko==0)
        return;
    int tt =0;
    bool kesken = true;
    while (kesken && tt < lkmt.size()) {
        if (indeksit[tt] == id) {
            ++lkmt[tt];
            kesken = false;
        }
        ++tt;
    }
    if (kesken) {
        lkmt.push_back(paljonko);
        indeksit.push_back(id);
    }
}



struct Mekaniikka {
    Mekaniikka(Infot in);
    Liikkeet liikkeet();
    void ostot(Liikkeet liikkeet);
  private:
    Infot info;
    Liikkeet valmistele_liikkeet();
    Liikkeet tee_liikkeet(Liikkeet liik);
    Ostot valmistele_ostot();
    void tee_ostot(Ostot ost_kohteet);
    void ekat_ostot(Ostot & ost);
    void tyhjien_taytto(Ostot & ost);
    void rautaa_rajalle(Ostot & ost);
} ;

Mekaniikka::Mekaniikka(Infot in) {
    info = in;
}
Liikkeet Mekaniikka::liikkeet() {
    return(tee_liikkeet(valmistele_liikkeet()));
}
void Mekaniikka::ostot(Liikkeet liikkeet) {
    info.kierroksen_puolivali(liikkeet);
    tee_ostot(valmistele_ostot());
}

Liikkeet Mekaniikka::valmistele_liikkeet() {
    Liikkeet tulos;
    std::vector <int> alueet = info.joukkoja(0); 
    for (int tt = 0; tt < alueet.size(); ++tt) {
        int joukkokoko = info.uhattunako(alueet[tt]);
        joukkokoko = std::max(joukkokoko, 1);
        joukkokoko = std::min(joukkokoko, 4); 
        int moneenko_suuntaan = (info.montako_omaa(alueet[tt])+1) / joukkokoko;
        std::vector<int> suun = info.suunnat(alueet[tt], moneenko_suuntaan);
        moneenko_suuntaan = suun.size();
        for (int ss = 0; ss < moneenko_suuntaan-1; ++ss) 
            if (suun[ss] != alueet[tt]) {
                tulos.lisaa_liike(alueet[tt], suun[ss], joukkokoko);
        }
        if (moneenko_suuntaan > 0 && suun[moneenko_suuntaan-1] != alueet[tt]) {
            int jaaneet = (joukkokoko == 1)? info.montako_omaa(alueet[tt]) - joukkokoko * (moneenko_suuntaan-1) : info.montako_omaa(alueet[tt]) % joukkokoko;
            if (jaaneet) {
                tulos.lisaa_liike(alueet[tt], suun[moneenko_suuntaan-1], jaaneet);
            }
        }
    }
    return(tulos);
}

Liikkeet Mekaniikka::tee_liikkeet(Liikkeet liik) {
    if (liik.lkmt.size() < 1) {
        std::cout << "WAIT";
    } else {
        for (int tt = 0; tt < liik.lkmt.size(); ++tt) 
            std::cout << liik.lkmt[tt] << " " << liik.lahto[tt] << " " << liik.kohde[tt] << " ";
    }
    std::cout << std::endl;
    return(liik);
}
Ostot Mekaniikka::valmistele_ostot() {
    Ostot tulos;
    info.lisaa_mannerten_painoarvot();
    if (info.eka_kierrosko()) {
        ekat_ostot(tulos);
        return(tulos);
    }
    if (info.varaa()) {
        tyhjien_taytto(tulos);
    }
    bool ei_ikisilmukkaa = true;
    int rahat_ennen(info.varaa());
    while (info.varaa() && ei_ikisilmukkaa) {
        rautaa_rajalle(tulos);
        if (info.varaa() == rahat_ennen)
            ei_ikisilmukkaa = false;
    }
    return(tulos);
}
void Mekaniikka::tyhjien_taytto(Ostot & ost) {
    std::vector<int> tyhj = info.parhaat_alueet(-1);
    if (tyhj.size() >0 && info.varaa() > 0) {
        int apu = 0;
        while (info.varaa() > 0 && apu < tyhj.size()) {
            ost.lisaa_idlle(tyhj[apu]);
            info.maksa(1, tyhj[apu]);
            ++apu;
        }
    }
}
void Mekaniikka::rautaa_rajalle(Ostot & ost) {
    std::vector<int> raja = info.parhaat_alueet(0);
    if (raja.size()==0) return;
    int kynnys;
    for (int tt = 0; tt < raja.size(); ++tt) 
        kynnys += info.houkutus(raja[tt]);
    kynnys = kynnys / 2 / raja.size();
    while (raja.size() > 2 && info.houkutus(raja[raja.size()-1]) < kynnys)
        raja.pop_back();
    unsigned kuhunkin = info.varaa() / raja.size();
    kuhunkin = (kuhunkin == 0) ? 1 : kuhunkin;
    int apu = 0;
    while (info.varaa() > 0 && apu < raja.size()) {
        ost.lisaa_idlle(raja[apu], kuhunkin);
        info.maksa(kuhunkin, raja[apu]);
        ++apu;
    }
}
void Mekaniikka::tee_ostot(Ostot ost) {
    std::vector<int> ost_maarat = ost.lkmt;
    std::vector<int> ost_kohteet = ost.indeksit;
    if (ost_kohteet.size() != ost_maarat.size()) {
        std::cout << "WAIT";
        std::cerr << "Virheelliset ostot!" << std::endl;
        return;
    }
    if (ost_kohteet.size() < 2) {
        std::cout << "WAIT";
    } else {
        for (int tt = 0; tt < ost_kohteet.size(); ++tt) 
            std::cout << ost_maarat[tt] << " " << ost_kohteet[tt] << " ";
    }
    std::cout << std::endl;
}
void Mekaniikka::ekat_ostot(Ostot & ost) {
    int kuinka_monta_reserviin = (rand() % 6); 
    while ((rand()%12) > kuinka_monta_reserviin  &&  kuinka_monta_reserviin < 10)
        ++kuinka_monta_reserviin;
    kuinka_monta_reserviin *= (info.pelaajia() - 2);

    std::vector<int> tyhj = info.parhaat_alueet(-1);
    int tt = rand() % 3;
    int r = 5 + rand() % 8;
std::cerr << "Tintataan joukkoja parhaisiin " << r << std::endl;
    while (tt < tyhj.size() && tt < r && info.varaa() > kuinka_monta_reserviin) { 
        int parhaaseen = (rand() % 6) % 3;
        parhaaseen = std::min(parhaaseen, info.varaa());
        parhaaseen = std::max(parhaaseen, 0);
        if (info.tuotot()[tyhj[tt]] < 4 || (parhaaseen == 2 && rand() % 2))
            parhaaseen = 0;
        ost.lisaa_idlle(tyhj[tt], parhaaseen );
std::cerr << "Parhaaseen meni " << parhaaseen << std::endl;
        info.maksa(parhaaseen, tyhj[tt]);
        tt += 1 + rand()%3;
    }
    tt = 0;
    while (tt < tyhj.size() && info.varaa() > kuinka_monta_reserviin) {
        ost.lisaa_idlle(tyhj[tt]);
        info.maksa(1, tyhj[tt]);
        tt = tt + 1 + rand() % 3;
    }
}


int main() {
      srand(time(NULL));
      int playerCount; 
      int myId; 
      int zoneCount; 
      int linkCount; 
      std::cin >> playerCount >> myId >> zoneCount >> linkCount;
      std::cin.ignore();
      
      std::vector <int> idt(zoneCount);
      std::vector <int> platinatuotot(zoneCount);
      std::vector <int> loput(linkCount);
      std::vector <int> alut(linkCount);
      std::vector <int> omistajat(zoneCount);
      std::vector <int> vihut(zoneCount);
      std::vector <int> omat(zoneCount);

      for (int i = 0; i < zoneCount; i++) {
         std::cin >> idt[i] >> platinatuotot[i];
         std::cin.ignore();
      }
      for (int i = 0; i < linkCount; i++) {
         std::cin >> alut[i] >> loput[i];
         std::cin.ignore();
      }

      Infot infot(playerCount, myId, idt, platinatuotot, alut, loput);
      
    while (1) {
        std::set<int> pelaajia_mukana;
        int platinum; 
        std::cin >> platinum;
        std::cin.ignore();
        for (int i = 0; i < zoneCount; i++) {
            int zId; 
            int ownerId; 
            int podsP0; 
            int podsP1; 
            int podsP2; 
            int podsP3; 
            std::cin >> zId >> ownerId >> podsP0 >> podsP1 >> podsP2 >> podsP3;
            std::cin.ignore();
            omistajat[zId] = ownerId;
            pelaajia_mukana.insert(ownerId);
            if (myId < 2) {
                    omat[zId] = (myId == 0) ? podsP0 : podsP1;
                } else {
                    omat[zId] = (myId == 2) ? podsP2 : podsP3;
                }
            vihut[zId] = podsP1 + podsP2 + podsP3 + podsP0 - omat[zId];
        }
        pelaajia_mukana.erase(-1);
        infot.kierroksen_alku(omistajat, vihut, omat, platinum/20, pelaajia_mukana);
        Mekaniikka mek(infot);
        Liikkeet liiks = mek.liikkeet();
        mek.ostot(liiks);
    }
}