local function isFree(positions, row, column, groupSize, peopleToBePlaced) --bool
  for _, position in ipairs(positions) do
    if position[1] == row and position[2] == column then
      return false
    elseif (row < position[1]) or ((position[1] == row) and (column < position[2])) then -- Suponiendo que las posiciones estan ordenadas
      return true
    end
  end
  return true
end

local function isLeftSameGroup(groupSize, peopleToBePlaced) --bool
  return peopleToBePlaced ~= groupSize
end

local function tryFromPosition(row, column, nRows, nColumns, aisleSeat, positions, groupSize) --bool
  local peopleToBePlaced = groupSize
  while column + peopleToBePlaced-1 <= nColumns do -- Con "+ peopleToBePlaced-1" no lo intenta si el número de personas faltante sobrepasa las columnas restantes
    if isFree(positions, row, column) then
      if (column ~= aisleSeat) and (column ~= aisleSeat+1) then
        peopleToBePlaced = peopleToBePlaced-1
      elseif (column == aisleSeat) and (isLeftSameGroup(groupSize, peopleToBePlaced)) then
        peopleToBePlaced = peopleToBePlaced-1
      elseif (column == aisleSeat+1) and (column+1 <= nColumns) and (isFree(positions, row, column+1)) and (peopleToBePlaced > 1) then
        peopleToBePlaced = peopleToBePlaced-2 -- Ya se que la siguiente columna existe, esta libre y por lo menos me faltan dos personas por añadir
        column = column+1
      else
        return false -- Alguien se hubiera quedado solo por el "aisleSeat"
      end
      if peopleToBePlaced == 0 then
        return true
      end
    else
      return false --"Ya esta ocupado"
    end
    column = column+1
  end
  return false --"Final de línea"
end

function getNumberOfGroups(nRows, nColumns, aisleSeat, positions, groupSize) --int
  local groupsPlaced = 0
  column = 1
  for row = 1, nRows do
    while column <= nColumns do
      if tryFromPosition(row, column, nRows, nColumns, aisleSeat, positions, groupSize) then
        groupsPlaced = groupsPlaced+1
        column = column + groupSize
      else
        column = column+1
      end
    end
    column = 1
  end
  return groupsPlaced
end
