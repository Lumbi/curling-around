import 'react'
import { useState } from 'react'
import { Parameter, isValid } from './parameter'
import { Button, Input, Table, TableHead, TableRow, TableCell, TableBody, Stack, Box, InputAdornment, IconButton } from '@mui/material'
import ErrorIcon from '@mui/icons-material/Error'
import DeleteIcon from '@mui/icons-material/Delete'
import AddIcon from '@mui/icons-material/Add'

export const App = () => {
    const [parameters, setParameters] = useState<Parameter[]>([{key: 'a', value: '1'}])

    const load = async (inputFile: File) => {
        setParameters([])
        const inputText = await inputFile?.text()
        const parameters = inputText
            .split('\n')
            .map(line => line.split('='))
            .map(([key, value]) => ({ key, value }))
        setParameters(parameters)
    }

    const updateParameter = (index: number, updatedParameter: Parameter) => {
        const updatedParameters = parameters
            .map((oldParameter, currentIndex) => {
                return currentIndex == index
                    ? updatedParameter
                    : oldParameter
            })
        setParameters(updatedParameters)
    }

    const appendParameter = () => {
        setParameters([...parameters, { key: '', value: ''}])
    }

    return (
        <>
            <Stack spacing={4} margin={4}>
                <Stack direction='row' spacing={4}>
                    <Input
                        type='file'
                        color='primary'
                        onChange={async (event) => {
                            const input = event.target as HTMLInputElement
                            const inputFile = input.files?.item(0)
                            if (inputFile) {
                                load(inputFile)
                            }
                        }}
                    />
                    <Box display='flex' justifyContent='flex-end'>
                        <Button variant='contained'>Save</Button>
                    </Box>
                </Stack>
                <ParameterTable
                    parameters={parameters}
                    updateParameter={updateParameter}
                />
                <Box display='flex' justifyContent='center'>
                    <IconButton onClick={appendParameter}>
                        <AddIcon/>
                    </IconButton>
                </Box>
            </Stack>
        </>
    )
}

type ParameterUpdater = {
    updateParameter: (index: number, parameter: Parameter) => void
}

type ParameterTableProps = {
    parameters: Parameter[]
} & ParameterUpdater

const ParameterTable = (props: ParameterTableProps) => {
    return (
        <Table>
            <TableHead>
            </TableHead>
            <TableBody>
            {
                props.parameters.map((parameter, index) =>
                    <ParameterRow
                        key={index}
                        index={index}
                        parameter={parameter}
                        updateParameter={props.updateParameter}
                    />
                )
            }
            </TableBody>
        </Table>
    )
}

type ParameterRowProps = {
    index: number,
    parameter: Parameter
} & ParameterUpdater

const ParameterRow = (props: ParameterRowProps) => {
    const isParameterValid = isValid(props.parameter)
    return (
        <>
            <TableRow>
                <TableCell>
                    <Input
                        type='text'
                        value={props.parameter.key}
                        onChange={(event) => props.updateParameter(
                            props.index,
                            { ...props.parameter, key: event.target.value }
                        )}
                        fullWidth={true}
                    />
                </TableCell>
                <TableCell>
                    <Input
                        type='text'
                        value={props.parameter.value}
                        error={!isParameterValid}
                        endAdornment={
                            <InputAdornment position='end'>
                                {
                                    !isParameterValid
                                        ? <ErrorIcon color='error'/>
                                        : null
                                }
                            </InputAdornment>
                        }
                        onChange={(event) => props.updateParameter(
                            props.index,
                            { ...props.parameter, value: event.target.value }
                        )}
                        fullWidth={true}
                    />
                </TableCell>
                <TableCell>
                    <IconButton>
                        <DeleteIcon/>
                    </IconButton>
                </TableCell>
            </TableRow>
        </>
    )
}
