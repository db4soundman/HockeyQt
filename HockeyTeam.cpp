#include "HockeyTeam.h"

HockeyTeam::HockeyTeam() {
    ppgToday = ppoppToday = pkToday = pkoppToday = 0;
}

const HockeyPlayer&
HockeyTeam::getPlayer(const int i) {
    return roster.at(i);
}

void
HockeyTeam::addPlayer(const HockeyPlayer player) {
    roster.append(player);
}

void
HockeyTeam::addPkFail() {
    pkopp++;
    pkoppToday++;
}
double HockeyTeam::getPkPct() const
{
    return pkPct;
}

void HockeyTeam::setPkPct(double value)
{
    pkPct = value;
}

double HockeyTeam::getPpPct() const
{
    return ppPct;
}

void HockeyTeam::setPpPct(double value)
{
    ppPct = value;
}

int HockeyTeam::getPkoppToday() const
{
    return pkoppToday;
}

void HockeyTeam::setPkoppToday(int value)
{
    pkoppToday = value;
}

int HockeyTeam::getPkToday() const
{
    return pkToday;
}

void HockeyTeam::setPkToday(int value)
{
    pkToday = value;
}

int HockeyTeam::getPpoppToday() const
{
    return ppoppToday;
}

void HockeyTeam::setPpoppToday(int value)
{
    ppoppToday = value;
}

int HockeyTeam::getPpgToday() const
{
    return ppgToday;
}

void HockeyTeam::setPpgToday(int value)
{
    ppgToday = value;
}

int HockeyTeam::getPkopp() const
{
    return pkopp;
}

void HockeyTeam::setPkopp(int value)
{
    pkopp = value;
}

int HockeyTeam::getPk() const
{
    return pk;
}

void HockeyTeam::setPk(int value)
{
    pk = value;
}

int HockeyTeam::getPpopp() const
{
    return ppopp;
}

void HockeyTeam::setPpopp(int value)
{
    ppopp = value;
}

int HockeyTeam::getPpg() const
{
    return ppg;
}

void HockeyTeam::setPpg(int value)
{
    ppg = value;
}


void
HockeyTeam::addPkStop() {
    pk++;
    pkopp++;
    pkToday++;
    pkoppToday++;
}

void
HockeyTeam::addPpFail() {
    ppopp++;
    ppoppToday++;
}

void
HockeyTeam::addPpg() {
    ppg++;
    ppopp++;
    ppgToday++;
    ppoppToday++;
}
