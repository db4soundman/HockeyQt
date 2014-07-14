#include "HockeyPlayer.h"

HockeyPlayer::HockeyPlayer() {
    goalsToday = assistsToday = ptsToday = penaltiesToday =
            pimToday = gaToday = savesToday = shotsFacedToday = 0;
}

HockeyPlayer::HockeyPlayer(const HockeyPlayer& p) {
    goalsToday = assistsToday = ptsToday = penaltiesToday =
            pimToday = gaToday = savesToday = shotsFacedToday = 0;

    name = p.getName();
    uni = p.getUni();
    year = p.getYear();
    plusMinus = p.getPlusMinus();
    gaavg = p.getGaavg();
    gp = p.getGp();
    goals = p.getGoals();
    assists = p.getAssists();
    pts = p.getPts();
    penalties = p.getPenalties();
    pim = p.getPim();
    ga = p.getGa();
    saves = p.getSaves();
    wins = p.getWins();
    losses = p.getLosses();
    shotsFaced = p.getShotsFaced();
}

QString HockeyPlayer::getName() const {
    return name;
}

void HockeyPlayer::setName(const QString& value) {
    name = value;
}
QString HockeyPlayer::getUni() const {
    return uni;
}

void HockeyPlayer::setUni(const QString& value) {
    uni = value;
}
QString HockeyPlayer::getYear() const {
    return year;
}

void HockeyPlayer::setYear(const QString& value) {
    year = value;
}

QString HockeyPlayer::getPlusMinus() const {
    return plusMinus;
}

void HockeyPlayer::setPlusMinus(const QString& value) {
    plusMinus = value;
}

int HockeyPlayer::getGp() const {
    return gp;
}

void HockeyPlayer::setGp(int value)
{
    gp = value;
}

int HockeyPlayer::getGoals() const {
    return goals;
}

void HockeyPlayer::setGoals(int value) {
    goals = value;
}
int HockeyPlayer::getAssists() const {
    return assists;
}

void HockeyPlayer::setAssists(int value) {
    assists = value;
}

int HockeyPlayer::getPts() const {
    return pts;
}

void HockeyPlayer::setPts(int value) {
    pts = value;
}

int HockeyPlayer::getPenalties() const {
    return penalties;
}

void HockeyPlayer::setPenalties(int value) {
    penalties = value;
}

int HockeyPlayer::getPim() const {
    return pim;
}

void HockeyPlayer::setPim(int value) {
    pim = value;
}

int HockeyPlayer::getGa() const {
    return ga;
}

void HockeyPlayer::setGa(int value) {
    ga = value;
}

int HockeyPlayer::getSaves() const {
    return saves;
}

void HockeyPlayer::setSaves(int value) {
    saves = value;
}
int HockeyPlayer::getShotsFaced() const {
    return shotsFaced;
}

void HockeyPlayer::setShotsFaced(int value) {
    shotsFaced = value;
}
int HockeyPlayer::getWins() const {
    return wins;
}

void HockeyPlayer::setWins(int value) {
    wins = value;
}
int HockeyPlayer::getLosses() const {
    return losses;
}

void HockeyPlayer::setLosses(int value) {
    losses = value;
}
int HockeyPlayer::getGoalsToday() const {
    return goalsToday;
}

void HockeyPlayer::setGoalsToday(int value) {
    goalsToday = value;
}
int HockeyPlayer::getAssistsToday() const {
    return assistsToday;
}

void HockeyPlayer::setAssistsToday(int value) {
    assistsToday = value;
}
int HockeyPlayer::getPtsToday() const {
    return ptsToday;
}

void HockeyPlayer::setPtsToday(int value) {
    ptsToday = value;
}
int HockeyPlayer::getPenaltiesToday() const {
    return penaltiesToday;
}

void HockeyPlayer::setPenaltiesToday(int value) {
    penaltiesToday = value;
}
int HockeyPlayer::getPimToday() const {
    return pimToday;
}

void HockeyPlayer::setPimToday(int value) {
    pimToday = value;
}
int HockeyPlayer::getGaToday() const {
    return gaToday;
}

void HockeyPlayer::setGaToday(int value) {
    gaToday = value;
}
int HockeyPlayer::getSavesToday() const {
    return savesToday;
}

void HockeyPlayer::setSavesToday(int value) {
    savesToday = value;
}
int HockeyPlayer::getShotsFacedToday() const {
    return shotsFacedToday;
}

void HockeyPlayer::setShotsFacedToday(int value) {
    shotsFacedToday = value;
}

QString HockeyPlayer::getGaavg() const
{
    return gaavg;
}

void HockeyPlayer::setGaavg(const QString& value)
{
    gaavg = value;
}

void HockeyPlayer::addSave()
{
    savesToday++;
    shotsFacedToday++;
}

void HockeyPlayer::minusSave()
{
    savesToday--;
    shotsFacedToday--;
}

void HockeyPlayer::addGa()
{
    gaToday++;
    shotsFacedToday++;
}

void HockeyPlayer::minusGa()
{
    gaToday--;
    shotsFacedToday--;
}
double HockeyPlayer::getSvPct() const
{
    return svPct;
}

void HockeyPlayer::calcSvPct()
{
    shotsFaced = ga + saves;
    svPct = ((double)saves / shotsFaced) * 100;
}


