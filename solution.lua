local function showPositions(positions)
  for _, data in ipairs(positions) do
    io.write('{ ')
    for _, value in pairs(data) do
      io.write(value, ' ')
    end
    io.write('}')
  end
  print()
end

local function isFree(positions, row, column)
  print("Compruebo: ", row, " ", column)
  for _, position in ipairs(positions) do
    if position[0] == row and position[1] == column then
      print("No libre")
      return false
    end
  end
  print("Libre")
  return true
end

function getNumberOfGroups(nRows, nColumns, aisleSeat, positions, groupSize)
  local maybeAlone = false
  local groupsPlaced = 0
  local peopleToBePlaced = groupSize
  for row = 1, nRows do
    for column = 1, nColumns do
      if isFree(positions, row, column) then
        if nColumns == column or nColumns + 1 == column then
          maybeAlone = true
        end
        peopleToBePlaced = peopleToBePlaced - 1
        if peopleToBePlaced == 0 then
          groupsPlaced = groupsPlaced + 1
          peopleToBePlaced = groupSize
          maybeAlone = false
        end
      end
    end
  end
  return groupsPlaced
end