import numpy as np

def GetMeanPenalties(filePaths):

    numAssigments = []
    consecutiveWorkingDays = []
    consecutiveFreeDays = []
    consecutiveWorkingWeekends = []
    maxWorkingWeekendsInFourWeeks = []
    completeWeekends = []
    identShiftTypesDuringWeekend = []
    noNightShiftBeforeFreeWeekend = []
    twoFreeDaysAfterNightShifts = []
    requestedDays = []
    requstedShifts = []
    alternativeSkillCategory = []
    unwantedPatterns = []

    for filePath in filePaths:
        with open(filePath) as f:
            penaltyLines = f.read().splitlines()
        for penaltyLine in penaltyLines:
            splitPenalty = penaltyLine.split()
            if len(splitPenalty) == 2:
                penaltyType = splitPenalty[0]
                penaltyValue = splitPenalty[1]
                if (penaltyType == "CheckNumAssigments:"):
                    numAssigments.append(penaltyValue)
                if (penaltyType == "CheckConsecutiveWorkingDays:"):
                    consecutiveWorkingDays.append(penaltyValue)
                if (penaltyType == "CheckConsecutiveFreeDays:"):
                    consecutiveFreeDays.append(penaltyValue)
                if (penaltyType == "CheckConsecutiveWorkingWeekends:"):
                    consecutiveWorkingWeekends.append(penaltyValue)
                if (penaltyType == "CheckMaxWorkingWeekendsInFourWeeks:"):
                    maxWorkingWeekendsInFourWeeks.append(penaltyValue)
                if (penaltyType == "CheckCompleteWeekends:"):
                    completeWeekends.append(penaltyValue)
                if (penaltyType == "CheckIdentShiftTypesDuringWeekend:"):
                    identShiftTypesDuringWeekend.append(penaltyValue)
                if (penaltyType == "CheckNoNightShiftBeforeFreeWeekend:"):
                    noNightShiftBeforeFreeWeekend.append(penaltyValue)
                if (penaltyType == "CheckTwoFreeDaysAfterNightShifts:"):
                    twoFreeDaysAfterNightShifts.append(penaltyValue)
                if (penaltyType == "CheckRequestedDays:"):
                    requestedDays.append(penaltyValue)
                if (penaltyType == "CheckRequstedShifts:"):
                    requstedShifts.append(penaltyValue)
                if (penaltyType == "CheckAlternativeSkillCategory:"):
                    alternativeSkillCategory.append(penaltyValue)
                if (penaltyType == "CheckUnwantedPatterns:"):
                    unwantedPatterns.append(penaltyValue)

    return (np.array(numAssigments).astype(np.float).mean(),
            np.array(consecutiveWorkingDays).astype(np.float).mean(),
            np.array(consecutiveFreeDays).astype(np.float).mean(),
            np.array(consecutiveWorkingWeekends).astype(np.float).mean(),
            np.array(maxWorkingWeekendsInFourWeeks).astype(np.float).mean(),
            np.array(completeWeekends).astype(np.float).mean(),
            np.array(identShiftTypesDuringWeekend).astype(np.float).mean(),
            np.array(noNightShiftBeforeFreeWeekend).astype(np.float).mean(),
            np.array(twoFreeDaysAfterNightShifts).astype(np.float).mean(),
            np.array(requestedDays).astype(np.float).mean(),
            np.array(requstedShifts).astype(np.float).mean(),
            np.array(alternativeSkillCategory).astype(np.float).mean(),
            np.array(unwantedPatterns).astype(np.float).mean())
